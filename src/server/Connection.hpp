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

    /**
     * @brief Contructor of the Connection class
     */
	Connection(void) = delete;

    /**
     * @brief Contructor of the Connection class
     * 
     * @param sock Socket accepted by the serveur
     * @param connectionManager Connection manager of the server
     * @param pipeline Server's pipeline use for modif the context
     * @param encryption Bool use to know if this will be in https or not
     */
    Connection(socket sock, ConnectionManager &connectionManager, oZ::Pipeline &pipeline, bool encryption= false);

    /**
     * @brief Start the connection between browser and serv (client)
     */
    void start(void);

    /**
     * @brief Stop the connection between browser and serv (client)
     */
    void stop(void);

private:

    /**
     * @brief Read the resquests from the browser
     */
    void read(void);

    /**
     * @brief Load and run the pipeline for modif context
     */
    void runPipeline(void);

    /**
     * @brief Send the context modified by the pipeline to the browser
     * 
     * @param context Context use during the pipeline
     */
    void send(oZ::Context &&context);

    /**
     * @brief Creste the response for the browser to by send
     * 
     * @param context Context use during the pipeline
     */
    std::string buildResponse(const oZ::Context &context);


    socket _socket;
    ConnectionManager &_connectionManager;
    oZ::Pipeline &_pipeline;
    bool _crypt;

    std::array<char, 8192> _buffer;
};
