/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** main
*/

#include "FileWatcher.hpp"

int main(void)
{
    FileWatcher fw("./config/config.json", std::chrono::milliseconds(5000));
    fw.start();
}