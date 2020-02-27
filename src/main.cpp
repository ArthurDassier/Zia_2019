/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** main
*/

#include <iostream>
#include <exception>
#include <server/Server.hpp>
#include <utils/EnvManager.hpp>

int main(int argc, char *argv[])
{
    std::string ip;
    int port;
    tls::EnvManager env("config/config.json");

    env.loadEnv();

    try {
        ip = (argc >= 2) ? argv[1] : Zia::DefaultIP;
        port = (argc >= 3) ? std::stoi(argv[2]) : Zia::DefaultPort;

        Zia::Server server(ip, port);
        server.run();
        server.close();
    } catch (const std::exception &e) {
        std::cerr << "An error has occured: " << e.what() << std::endl;
        return 84;
    }
    return 0;
}