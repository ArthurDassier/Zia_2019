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
	ConnectionManager() = default;

    void addClient(ConnectionPtr);

    void eraseClient(ConnectionPtr);

    void eraseAll(void);
private:

    std::set<ConnectionPtr> _connections;
};
