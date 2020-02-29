/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** Log
*/

#pragma once

#include <string>

namespace Zia
{
    class Log;
}

/**
 * @brief Log class to manage the log.
 */
class Zia::Log {
public:
    static void setPathFile(const std::string &) noexcept;

    static void info(const std::string &msg, bool writeInFile = false) noexcept;
    static void warning(const std::string &msg, bool writeInFile = false) noexcept;
    static void critical(const std::string &msg, bool writeInFile = false) noexcept;

    static long NumbersInfo;
    static long NumbersWarning;
    static long NumbersCritical;

private:
    static std::string _pathFile;

	Log() = delete;
};