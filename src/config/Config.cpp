/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** Config
*/

#include "Config.hpp"

using namespace cfg;

Config::Config(const FileDescriptor &file, const std::string &name):
    _name(name),
    _path(file.path()),
    _timestamp(file.last_write_time())
{
}

void Config::loadConfig(const std::filesystem::path &path)
{
    std::ifstream file(path);
    json j;
    file >> j;

    file.close();
    std::string s = j.dump();
    std::cout << _name << ":" << std::endl;

    // Load each attributes...
    for (auto &[key, value]: j.items())
        std::cout << key << ": " << value << std::endl;
}

void Config::update(const FileStatus &status)
{
    switch (status) {
        case FileStatus::modified:
            loadConfig(_path);
            break;
        case FileStatus::erased:
            std::cout << "ERASED MOTAFUCKA" << std::endl;
            break;
        default:
            std::cout << "Nothing to do bro" << std::endl;
            break;
    }
}

void Config::setName(const std::string &name)
{
    _name = name;
}

const std::string Config::getName() const noexcept
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

void Config::setTimestamp(const Timestamp &timestamp)
{
    _timestamp = timestamp;
}

Timestamp Config::getTimestamp() const noexcept
{
    return _timestamp;
}