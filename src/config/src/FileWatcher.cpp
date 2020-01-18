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
    _timestamp(std::filesystem::last_write_time(_file_to_watch)),
    _delay(delay)
{
}

FileWatcher::FileWatcher()
{
}

FileWatcher::~FileWatcher()
{
}

void FileWatcher::start()
{
    auto timestamp = std::filesystem::last_write_time(_file_to_watch);
    key = SharedMemory::key_gen(_file_to_watch, 65);
    shmid = SharedMemory::shm_id_gen(key, 1024, IPC_CREAT);

    SharedMemory shrd_mm;

    while (_running) {
        std::this_thread::sleep_for(_delay);
        if (!std::filesystem::exists(_file_to_watch)) {
            std::cout << "File at path " << _file_to_watch
                      << " doesn't exists." << std::endl;
            _running = false;
            shrd_mm.write_data(key, 1024, IPC_CREAT, "erased");
            continue;
        }
        auto current_file_timestamp = std::filesystem::last_write_time(_file_to_watch);
        std::time_t cftime = decltype(current_file_timestamp)::clock::to_time_t(current_file_timestamp);
        std::cout << "Current:" << std::asctime(std::localtime(&cftime));

        std::time_t cftime2 = decltype(timestamp)::clock::to_time_t(timestamp);
        std::cout << "Previous:" << std::asctime(std::localtime(&cftime2));
        if (timestamp != current_file_timestamp)
        {
            timestamp = current_file_timestamp;
            std::cout << "Reload config" << std::endl;
            shrd_mm.write_data(key, 1024, IPC_CREAT, "modified");
        } else {
            std::cout << "Nothing to do" << std::endl;
            shrd_mm.write_data(key, 1024, IPC_CREAT, "none");
        }
    }
}

// time_t FileWatcher::getTimeStamp() const noexcept
// {
//     // return _timestamp;
// }