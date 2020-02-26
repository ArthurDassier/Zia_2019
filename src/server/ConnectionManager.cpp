/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** ConnectionManager
*/

#include "ConnectionManager.hpp"
#include <iostream>

void Zia::ConnectionManager::addClient(ConnectionPtr c)
{
    _connections.insert(c);
    c->start();
}

void Zia::ConnectionManager::eraseClient(ConnectionPtr c)
{
    _connections.erase(c);
    c->stop();
}

void Zia::ConnectionManager::eraseAll(void)
{
    for (auto c : _connections)
        c->stop();
    _connections.clear();
    // std::cout << "destruction" << std::endl;
}