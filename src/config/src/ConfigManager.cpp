/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** ConfigManager
*/

#include "ConfigManager.hpp"

cfg::ConfigManager::ConfigManager(const std::string &path)
{
    // std::cout << "Config path: " << std::getenv("CONFIG_PATH") << std::endl;
    setConfigPath(path);
}

cfg::ConfigManager::~ConfigManager()
{
    for (auto &it : _configs)
        delete it.second;
}

void cfg::ConfigManager::manage()
{
    for (auto &it : _configs) {
        std::thread t(&Config::update, it.second);
        t.detach();
    }
}

void cfg::ConfigManager::setConfigPath(const std::string &path)
{
    for (const auto &file : std::filesystem::recursive_directory_iterator(path)) {
        std::string filename = std::filesystem::path(
            file.path().string()).filename();
        std::size_t last_index = filename.find_last_of(".");
        std::string raw_name = filename.substr(0, last_index);
        auto config = new Config(file);
        config->setName(raw_name);
        _configs[raw_name] = std::move(config);
    }
}

cfg::Config *cfg::ConfigManager::getConfig(const std::string &config_name)
{
    auto config = _configs.find(config_name);
    
    if (config != _configs.end())
        return config->second;
    return nullptr;
}