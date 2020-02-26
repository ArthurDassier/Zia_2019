/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** main
*/

#include <iostream>
#include <exception>
#include <server/Server.hpp>

int main(int argc, char *argv[])
{
    std::string ip;
    int port;

    std::string cwd = std::filesystem::current_path().string();
    std::stringstream modules_path;
    std::stringstream tmp_modules_path;

    modules_path << cwd << std::string("/lib/modules/");
    tmp_modules_path << cwd << std::string("/lib/tmp_modules/");

    setenv("MODULES_PATH", modules_path.str().c_str(), 1);
    setenv("TMP_MODULES_PATH", tmp_modules_path.str().c_str(), 1);

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