/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** ConnectionManager
*/

#pragma once

#include <set>
#include "Connection.hpp"

namespace Zia
{
    class ConnectionManager;
    class Connection;
}

typedef std::shared_ptr<Zia::Connection> ConnectionPtr;

class Zia::ConnectionManager {
public:

    /**
     * @brief Cronstructor for the connection manager
     */
    ConnectionManager() = default;

    /**
     * @brief Add a client give to the manager in the list
     * 
     * @param client Pointer on the client
     */
    void addClient(ConnectionPtr client);

    /**
     * @brief Remove a client give to the manager to the list
     * 
     * @param client Pointer on the client
     */
    void eraseClient(ConnectionPtr client);

    /**
     * @brief Add a client give to the manager in the list
     * 
     */
    void eraseAll(void);

private:
    std::set<ConnectionPtr> _connections;
};
