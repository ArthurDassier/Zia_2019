/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** ConfigManager
*/

#include "ConfigManager.hpp"

ConfigManager::ConfigManager(const std::string &path)
{
    // std::cout << "Config path: " << std::getenv("CONFIG_PATH") << std::endl;
    setConfigPath(path);

    for (const auto &it : _configs)
        std::cout << it.first << ": " << it.second->getPath().string() << std::endl;
}

ConfigManager::~ConfigManager()
{
    for (auto &it : _configs)
        delete it.second;
}

void ConfigManager::manage()
{
    for (auto &it : _configs)
        it.second->update();
}

void ConfigManager::setConfigPath(const std::string &path)
{
    for (const auto &file : std::filesystem::recursive_directory_iterator(path)) {
        std::string filename = std::filesystem::path(
            file.path().string()).filename();
        std::size_t last_index = filename.find_last_of(".");
        std::string raw_name = filename.substr(0, last_index);
        // _configs[raw_name] = std::make_shared<Config>(Config(file));
        _configs[raw_name] = new Config(file);
        std::cout << _configs[raw_name]->getPath() << std::endl;
    }
}

// std::shared_ptr<Config> ConfigManager::getConfig(const std::string &config_name)
// {
//     auto config = _configs.find(config_name);

//     if (config != _configs.end())
//         return std::move(config->second);
//     return nullptr;
// }