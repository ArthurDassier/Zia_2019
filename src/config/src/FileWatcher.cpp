/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** FileWatcher
*/

#include "FileWatcher.hpp"


FileWatcher::FileWatcher(const std::string &path,
    const std::chrono::duration<int, std::milli> delay) :
    _running(true),
    _file_to_watch(path),
    // _timestamp(0),
    _delay(delay)
{
    // struct stat st;

    // if (stat(file.c_str(), &st) != 0) {
    //     printf("Some error message with arg: {}\n", 1);
    // }
    printf("Stat is working\n");
    // _timestamp = st.st_mtime;
    _timestamp = std::filesystem::last_write_time(path);
    std::time_t cftime = decltype(_timestamp)::clock::to_time_t(_timestamp);
    std::cout << std::asctime(std::localtime(&cftime)) << std::endl;
    // std::cout << _timestamp << std::endl;
}

FileWatcher::~FileWatcher()
{
}

void FileWatcher::start() {
    while (_running) {
        std::this_thread::sleep_for(_delay);
        if (!std::filesystem::exists(_file_to_watch)) {
            std::cout << "File at path " << _file_to_watch
                      << " doesn't exists." << std::endl;
            _running = false;
        }
        // auto current_file_timestamp = std::filesystem::last_write_time(_file_to_watch);
        // if (_timestamp != current_file_timestamp) {
        //     _timestamp = current_file_timestamp;
        //     std::cout << "Reload config" << std::endl;
        // }
    }
}

// time_t FileWatcher::getTimeStamp() const noexcept
// {
//     // return _timestamp;
// }