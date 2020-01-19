/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** FileWatcher
*/

#include "FileWatcher.hpp"

cfg::FileWatcher::FileWatcher(const std::string &path,
    const std::chrono::duration<int, std::milli> delay):
    _running(true),
    _file(path),
    _timestamp(std::filesystem::last_write_time(_file)),
    _delay(delay)
{
    _key = SharedMemory::key_gen(_file, 65);
}

void cfg::FileWatcher::start()
{
    SharedMemory    shrd_mm;
    FileStatus      fs;

    while (_running) {
        std::ostringstream stream;
        fs = FileStatus::none;

        std::this_thread::sleep_for(_delay);
        if (std::filesystem::exists(_file)) {
            auto current_timestamp = std::filesystem::last_write_time(_file);

            if (_timestamp != current_timestamp) {
                _timestamp = current_timestamp;
                fs = FileStatus::modified;
            }
        } else {
            std::cout << "File at path " << _file
                        << " doesn't exists." << std::endl;
            _running = false;
            fs = FileStatus::erased;
        }
        stream.clear();
        stream << fs;
        shrd_mm.write_data(_key, 1024, IPC_CREAT, stream.str().c_str());
    }
}