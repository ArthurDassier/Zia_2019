/*
** EPITECH PROJECT, 2020
** openZia
** File description:
** OperatingSystem
*/

#pragma once

#if defined(__linux__) || defined(__linux) || defined(linux) || defined(_LINUX)
    #define SYSTEM_LINUX
#elif defined(_WIN32) || defined(_WIN64)
    #define SYSTEM_WINDOWS
#else
    #error "Operating System not supported by openZia"
#endif