/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** FileWatcher
*/

#pragma once

#include <chrono>
#include <ctime>
#include <filesystem>
#include <functional>
#include <future>
#include <iostream>
#include <string>
#include <thread>

#include "SharedMemory.hpp"

enum class FileStatus
{
    created,
    modified,
    erased,
    none
};
class FileWatcher {
	public:
        FileWatcher();
        FileWatcher(const std::string &,
                    const std::chrono::duration<int, std::milli> delay);
        ~FileWatcher();

        void start();
            // const std::string &,
            // const std::chrono::duration<int, std::milli> delay,
            // const std::function<void(FileStatus)> &);

        time_t getTimeStamp() const noexcept;

    private:
        bool                                    _running;
        // const std::string   _file_to_watch;
        std::filesystem::path                   _file_to_watch;
        // time_t              _timestamp;
        std::filesystem::file_time_type         _timestamp;
        std::chrono::duration<int, std::milli>  _delay;

        key_t key;
        int shmid;
};