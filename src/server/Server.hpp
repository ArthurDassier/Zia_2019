/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** ServerHTTP
*/

#pragma once

#include <thread>
#include <boost/asio.hpp>
#include <openZia/Pipeline.hpp>
#include <config/ConfigManager.hpp>
#include "ConnectionManager.hpp"
#include "ServerConfig.hpp"

namespace Zia
{
    class Server;

    const int DefaultPort = 80;
    const int DefaultPortHTTPS = 443;
    const std::string DefaultIP = "127.0.0.1";
}


class Zia::Server: protected oZ::Pipeline
{
public:
    using ConfigPtr = std::shared_ptr<ServerConfig>;
    using io_service = boost::asio::io_service;
    using acceptor = boost::asio::ip::tcp::acceptor;
    using socket = boost::asio::ip::tcp::socket;

    Server(const std::string &ip = DefaultIP, int port = DefaultPort,
        std::string &&modules = "lib/tmp_modules",
        std::string &&configs = "lib/modules/Configs");

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

    void addEnabledModules(const EnabledList &modulesList);

private:

    oZ::Pipeline _pipeline;

    std::vector<std::thread> _threads;

    cfg::ConfigManager _configManager;
    ConnectionManager _connectionManager;
    ConfigPtr _serverConfig;

    io_service _io_service;
    acceptor _acceptor;
    acceptor _acceptorHTTPS;
    socket _socket;
    boost::asio::signal_set _signals;

    std::string _ip;
    int _port;
};
