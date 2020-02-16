/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** Log
*/

#include "Log.hpp"
#include <iomanip>
#include <iostream>

long Zia::Log::NumbersInfo = 0;
long Zia::Log::NumbersWarning = 0;
long Zia::Log::NumbersCritical = 0;

void Zia::Log::setPathFile(const std::string &path) noexcept
{

}

void Zia::Log::info(const std::string &msg, bool writeInFile) noexcept
{
    NumbersInfo++;
    std::string str = "[Info ";
    std::cout << str << std::setfill('0') << std::setw(5) << NumbersInfo << "] " << msg << std::endl;
}

void Zia::Log::warning(const std::string &msg, bool writeInFile) noexcept
{
    NumbersWarning++;
    std::string str = "[Warning ";
    std::cout << str << std::setfill('0') << std::setw(5) << NumbersWarning << "] " << msg << std::endl;
}

void Zia::Log::critical(const std::string &msg, bool writeInFile) noexcept
{
    NumbersCritical++;
    std::string str = "[!CRITICAL! ";
    std::cout << str << std::setfill('0') << std::setw(5) << NumbersCritical << "] " << msg << std::endl;
}