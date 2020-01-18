/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** main
*/

#include "ConfigManager.hpp"

int main(void)
{
    ConfigManager cm("./config");

    // std::cout << cm.getConfig("config")->getPath() << std::endl;
    // FileWatcher fw("./config", std::chrono::milliseconds(5000));
    // fw.start();
    while (1)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        cm.manage();
    }
}