/*
** EPITECH PROJECT, 2020
** CCP_zia_2019
** File description:
** SharedMemory
*/

#pragma once

#include <list>
#include <stdio.h>
#include <string>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
// #include "Plazza.hpp"

class SharedMemory {
    public:
        SharedMemory() = default;
        ~SharedMemory() = default;

        void write_data(key_t, size_t, size_t, std::string);
        char *get_data(key_t, size_t, size_t) const;
        char *get_data_by_id(int) const;
        void detach_from(const void *);

        static void destroy(int, int);

        static key_t key_gen(std::string, int);
        static int shm_id_gen(key_t, size_t, size_t);
};