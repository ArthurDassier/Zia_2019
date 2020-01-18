/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** Config
*/

#include "Config.hpp"

void func(std::promise<bool> && p) {
    p.set_value(true);
}

Config::Config(const std::filesystem::directory_entry &file):
    _path(file.path()),
    _timestamp(file.last_write_time()),
    _fw(file.path(), std::chrono::milliseconds(5000))
{
    key = SharedMemory::key_gen(_path, 65);
    shmid = SharedMemory::shm_id_gen(key, 1024, IPC_CREAT);

    std::thread th1(&FileWatcher::start, _fw);
    th1.detach();
}

void Config::loadConfig(const std::filesystem::path &config_path)
{

}

void Config::update()
{
    SharedMemory shrd_mm;
    key = SharedMemory::key_gen(_path, 65);
    shmid = SharedMemory::shm_id_gen(key, 1024, IPC_CREAT);
    char *str = shrd_mm.get_data_by_id(shmid);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << "Update: " << str << std::endl;
    shrd_mm.detach_from(str);
    SharedMemory::destroy(shmid, IPC_RMID);
}

void Config::setName(const std::string &name)
{
    _name = name;
}

std::string Config::getName() const noexcept
{
    return _name;
}

void Config::setPath(const std::filesystem::path &path)
{
    _path = path;
}

std::filesystem::path Config::getPath() const noexcept
{
    return _path;
}

std::filesystem::file_time_type Config::getTimestamp() const noexcept
{
    return _timestamp;
}