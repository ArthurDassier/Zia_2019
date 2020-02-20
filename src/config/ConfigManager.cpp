/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** ConfigManager
*/

#include "ConfigManager.hpp"

cfg::ConfigManager::ConfigManager(const std::string &path):
    _path(path)
{
    // std::cout << "Config path: " << std::getenv("CONFIG_PATH") << std::endl;
    loadConfigDir();
}

void cfg::ConfigManager::manage()
{
    for (auto &config : _configs) {
        config.second = ThreadPtr(new std::thread(&Config::update, config.first));
        config.second->detach();
    }
}

void cfg::ConfigManager::stop()
{
    for (auto &config : _configs) {
        config.second->join();
    }
}

void cfg::ConfigManager::loadConfigDir()
{
    for (const auto &file : std::filesystem::recursive_directory_iterator(_path)) {
        std::string name = getConfigName(file);
        ConfigPtr config = ConfigPtr(new Config(file, name));
        _configs.emplace_back(std::pair(std::move(config), nullptr));
    }
}

void cfg::ConfigManager::setConfigPath(const std::string &path)
{
    _path = path;
}

const std::string cfg::ConfigManager::getConfigPath() const noexcept
{
    return _path;
}

cfg::ConfigPtr cfg::ConfigManager::getConfig(const std::string &config_name) const
{
    for (const auto &config : _configs)
        if (!config.first->getName().compare(config_name))
            return config.first;
    // auto config = _configs.find(config_name);
    
    // if (config != _configs.end())
    //     return config->second.first;
    return nullptr;
}

const std::string cfg::ConfigManager::getConfigName(const FileDescriptor &file) const
{
    std::string filename = std::filesystem::path(
        file.path().string()).filename();
    std::size_t last_index = filename.find_last_of(".");
    const std::string name = filename.substr(0, last_index);

    return name;
}