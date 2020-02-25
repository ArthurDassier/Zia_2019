/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** Connection
*/

#include <iostream>
#include <vector>
#include <iterator>
#include <array>
#include <utility>
#include "Connection.hpp"
#include "Log.hpp"
#include <modules/SSL/SSLModule.hpp>

Zia::Connection::Connection(socket sock, ConnectionManager &c, oZ::Pipeline &pipeline)
:
    _socket(std::move(sock)),
    _connectionManager(c),
    _pipeline(pipeline)
{}

void Zia::Connection::start(void)
{
    Log::info("New client\n> IP\t" + _socket.remote_endpoint().address().to_string());
    read();
}

void Zia::Connection::read(void)
{
    auto self(shared_from_this());
    _socket.async_read_some(boost::asio::buffer(_buffer),
    [this, self](boost::system::error_code error, std::size_t bytes)
    {
        if (error && error != boost::asio::error::operation_aborted) {
            _connectionManager.eraseClient(shared_from_this());
            return;
        }
        runPipeline();
    });
}

void Zia::Connection::runPipeline(void)
{
    std::string str(_buffer.data());

    oZ::ByteArray arr(str.size());

    std::transform(str.begin(), str.end(), arr.begin(),
    [](char c)
    {
      return static_cast<char>(c);
    });

    oZ::Packet packet(std::move(arr), oZ::Endpoint(_socket.remote_endpoint().address().to_string(), _socket.remote_endpoint().port()));
    oZ::Context context(std::move(packet));

    int fd = _socket.native_handle();
    _pipeline.runPipeline(context);
    send(std::move(context));
}

void Zia::Connection::send(oZ::Context &&context)
{
    std::string response(
        "HTTP/"
        + std::to_string(context.getResponse().getVersion().majorVersion)
        + "."
        + std::to_string(context.getResponse().getVersion().minorVersion) 
        + " "
        + std::to_string(static_cast<int>(context.getResponse().getCode())) 
        + " " 
        + context.getResponse().getReason() + "\n"
        + "Content-Length: " + context.getResponse().getHeader().get("Content-Length") + "\n"
        + "Content-Type: " + context.getResponse().getHeader().get("Content-Type") + "\n\n"
        + context.getResponse().getBody()
    );

    auto self(shared_from_this());
    boost::asio::async_write(_socket, boost::asio::buffer(response),
    [this, self](boost::system::error_code error, std::size_t)
    {
        if (error && error != boost::asio::error::operation_aborted) {
            _connectionManager.eraseClient(shared_from_this());
            return;
        }
        boost::system::error_code err;
        _socket.shutdown(socket::shutdown_both, err);
    });
}

void Zia::Connection::stop(void)
{
    Log::info("Client disconnected");
}