/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** Module
*/

#include "Module.hpp"

using namespace Zia;

Module::Module(const cfg::FileDescriptor &path):
    _name(getName(path)),
    _path(path.path())
{
}

const std::string Module::getName() const noexcept
{
    return _name;
}

const std::string Module::getName(const cfg::FileDescriptor &file) const
{
    std::string filename = std::filesystem::path(
                               file.path().string())
                               .filename();
    std::size_t last_index = filename.find_last_of(".");
    const std::string name = filename.substr(0, last_index);
    return name;
}

const std::string Module::getPath() const noexcept
{
    return _path;
}
