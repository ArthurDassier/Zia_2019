/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** ServerHTTP
*/

#pragma once

#include <thread>
#include <boost/asio.hpp>
#include "openZia/Pipeline.hpp"
#include "ConnectionManager.hpp"

namespace Zia
{
    class Server;

    const int DefaultPort = 80;
    const std::string DefaultIP = "127.0.0.1";
}


class Zia::Server
{
public:

    using io_service = boost::asio::io_service;
    using acceptor = boost::asio::ip::tcp::acceptor;
    using socket = boost::asio::ip::tcp::socket;

	Server(const std::string &ip = DefaultIP, int port = DefaultPort,
        std::string &&modules = "build/Modules",
        std::string &&configs = "build/Modules/Configs");

    /**
     * @brief Run Server
     *
     */
    void run();

    /**
     * @brief Close Server
     *
     */
    void close();

private:

    /**
     * @brief Waiting async client method
     *
     */
    void WaitingClient(void);

    /**
     * @brief Get signals of server and execute them
     *
     */
    void ManagingSignals(void);

private:

    oZ::Pipeline _pipeline;

    std::vector<std::thread> _threads;

    ConnectionManager _connectionManager;

    io_service _io_service;
    acceptor _acceptor;
    socket _socket;
    boost::asio::signal_set _signals;

    std::string _ip;
    int _port;
};
