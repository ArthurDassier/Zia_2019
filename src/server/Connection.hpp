/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** Connection
*/

#pragma once

#include <array>
#include <memory>
#include <boost/asio.hpp>
#include "openZia/Pipeline.hpp"
#include "ConnectionManager.hpp"

namespace Zia
{
    class Connection;
    class ConnectionManager;
}

class Zia::Connection : public std::enable_shared_from_this<Zia::Connection>
{
public:
    using socket = boost::asio::ip::tcp::socket;

	Connection(void) = delete;

    Connection(socket sock, ConnectionManager &, oZ::Pipeline &, bool = false);

    void start(void);

    void stop(void);

private:

    void read(void);
    void runPipeline(void);
    void send(oZ::Context &&);

    socket _socket;
    ConnectionManager &_connectionManager;
    oZ::Pipeline &_pipeline;
    bool _crypt;

    std::array<char, 8192> _buffer;
};
