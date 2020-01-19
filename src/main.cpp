/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** main
*/

#include "ConfigManager.hpp"

int main(void)
{
    cfg::ConfigManager cm("./config");

    std::string cmd;
    cm.manage();

    while (1) {
        std::getline(std::cin, cmd);
        std::cout << "===== " << cm.getConfig("config")->getName() << std::endl;
    }
}