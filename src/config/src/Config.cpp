/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** Config
*/

#include "Config.hpp"

cfg::Config::Config(const std::filesystem::directory_entry &file):
    _path(file.path()),
    _timestamp(file.last_write_time()),
    _fw(file.path(), std::chrono::milliseconds(5000))
{
    _key    = SharedMemory::key_gen(_path, 65);
    _shmid  = SharedMemory::id_gen(_key, 1024, IPC_CREAT);

    std::thread th1(&FileWatcher::start, _fw);
    th1.detach();
}

void cfg::Config::loadConfig(const std::filesystem::path &config_path)
{
    std::cout << "====LOAD CONFIG====" << std::endl;

    std::ifstream file(config_path);

    file.close();
}

void cfg::Config::update()
{
    SharedMemory shrd_mm;
    
    while (1) {
        _key        = SharedMemory::key_gen(_path, 65);
        _shmid      = SharedMemory::id_gen(_key, 1024, IPC_CREAT);
        char *str   = shrd_mm.get_data_by_id(_shmid);

        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        // std::cout << _path << " update: " << str << std::endl;
        if (std::strcmp(str, "modified\n") == 0)
            loadConfig(_path);
        else if (std::strcmp(str, "erased\n") == 0)
            std::cout << "ERASED!!!" << std::endl;
        // setName(str);
        shrd_mm.detach_from(str);
        SharedMemory::destroy(_shmid, IPC_RMID);
    }
}

void cfg::Config::setName(const std::string &name)
{
    _name = name;
}

std::string cfg::Config::getName() const noexcept
{
    return _name;
}

void cfg::Config::setPath(const std::filesystem::path &path)
{
    _path = path;
}

std::filesystem::path cfg::Config::getPath() const noexcept
{
    return _path;
}

std::filesystem::file_time_type cfg::Config::getTimestamp() const noexcept
{
    return _timestamp;
}