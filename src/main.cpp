/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** main
*/

/*!
 * \file main.c
 * \brief Main fonction
 * \author Arthur.D
 * \version 1.0
 * \date 29 fevrier 2020
 *
 * \mainpage Zia Program
 * \ Main page
 * 
 */

#include <iostream>
#include <exception>
#include <server/Server.hpp>
#include <utils/EnvManager.hpp>

/*!
 * \fn int main(int ac, char **av)
 * \brief Briefly checks for errors and launch the core
 *
 * \param int ac, char **av and the char **env variables
 * \return 0 if everything went ok or 84 is case of errors
 */

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