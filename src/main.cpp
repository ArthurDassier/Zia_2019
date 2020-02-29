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
        std::filesystem::directory_entry de;
        std::filesystem::path config_path("config/server_config.json");
        de.assign(config_path);
        auto config = Zia::ServerConfig(de, "server_config");

        Zia::Server server(std::make_shared<Zia::ServerConfig>(config));
        server.run();
        server.close();
    } catch (const std::exception &e) {
        std::cerr << "An error has occured: " << e.what() << std::endl;
        return 84;
    }
    return 0;
}