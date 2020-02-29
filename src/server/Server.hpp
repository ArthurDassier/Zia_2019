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
    class Server: protected oZ::Pipeline
    {
        public:
            using ConfigPtr = std::shared_ptr<ServerConfig>;

            using io_service = boost::asio::io_service;

            using Acceptor = boost::asio::ip::tcp::acceptor;
            
            using Socket = boost::asio::ip::tcp::socket;

            using Endpoint = boost::asio::ip::tcp::endpoint;

            Server(const ConfigPtr &config);

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

            void setAcceptor(Acceptor &acceptor, Endpoint &endpoint);

            void addEnabledModules(const EnabledList &modulesList);

        private:
            oZ::Pipeline _pipeline;
            cfg::ConfigManager _configManager;
            ConnectionManager _connectionManager;
            ConfigPtr _serverConfig;

            io_service _io_service;
            Acceptor _acceptor;
            Acceptor _acceptorHTTPS;
            Socket _socket;
            boost::asio::signal_set _signals;

            std::string _ip;
            int _port;
    };
}; // namespace Zia