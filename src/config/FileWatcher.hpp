/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** FileWatcher
*/

#pragma once

#include <chrono>
#include <cstring>
#include <ctime>
#include <filesystem>
#include <functional>
#include <future>
#include <iostream>
#include <string>
#include <thread>

#include <utils/SharedMemory.hpp>

namespace cfg {
    enum class FileStatus
    {
        created,
        modified,
        erased,
        none
    };

    static std::ostream& operator<<(std::ostream& os, FileStatus& fs)
    {
        switch (fs)
        {
            case FileStatus::created:   return os << "created";
            case FileStatus::modified:  return os << "modified";
            case FileStatus::erased:    return os << "erased";
            default:                    return os << "none";
        };
    }

    static FileStatus operator<<(FileStatus& s, const char *fs)
    {
        if (std::strcmp(fs, "created") == 0)    return s = FileStatus::created;
        if (std::strcmp(fs, "modified") == 0)   return s = FileStatus::modified;
        if (std::strcmp(fs, "erased") == 0)     return s = FileStatus::erased;
        return s = FileStatus::none;
    }

    class FileWatcher {
        public:
            FileWatcher(const std::string &,
                        const std::chrono::duration<int, std::milli> delay);
            ~FileWatcher() = default;

            void start();

        private:
            key_t _key;
            bool _running;
            std::filesystem::path _file;
            std::filesystem::file_time_type _timestamp;
            std::chrono::duration<int, std::milli> _delay;
    };
}; // namespace cfg