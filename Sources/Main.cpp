/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** Main
*/

#include <iostream>
#include <exception>
#include "Server.hpp"

int main(int argc, char *argv[])
{
    std::string ip;
    int port;

    std::cout << "TRY" << std::endl;

    try {
        ip = (argc >= 2) ? argv[1] : Zia::DefaultIP;
        port = (argc >= 3) ? std::stoi(argv[2]) : Zia::DefaultPort;

        Zia::Server server(ip, port);
        std::cout << "Server created" << std::endl;
        server.run();
        server.close();
    } catch (const std::exception &e) {
        std::cerr << "Main: " << e.what() << std::endl;
        return (84);
    }
    return (0);
}