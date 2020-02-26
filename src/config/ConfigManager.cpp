/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** ConfigManager
*/

#include "ConfigManager.hpp"

using namespace cfg;

ConfigManager::ConfigManager(const std::string &path):
    _path(path),
    _timeSleep(5000),
    _onChangeCallback([]() {}),
    _onErasedCallback([]() {}),
    _thread(nullptr),
    _watching(false)
{
    loadConfigDir(_path);
}

ConfigManager::ConfigManager():
    _path(std::getenv("CONFIG_PATH")),
    _timeSleep(5000),
    _onChangeCallback([]() {}),
    _onErasedCallback([]() {}),
    _thread(nullptr),
    _watching(false)
{
    loadConfigDir(_path);
}

void ConfigManager::manage()
{
    watching(true);
    _thread = ThreadPtr(new std::thread(&ConfigManager::watch, this));
    _thread->detach();
}

void ConfigManager::stop()
{
    watching(false);
    _thread->join();
}

void ConfigManager::watch()
{
    while (isWatching()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        FileStatus status = FileStatus::none;

        for (auto &it : _configs)
            if (!std::filesystem::exists(it->getPath())) {
                status = FileStatus::erased;
                it->update(status);
                _onErasedCallback();
            }

        for (const auto &file : std::filesystem::recursive_directory_iterator(_path)) {
            auto current_timestamp = std::filesystem::last_write_time(file);
            std::string name = getConfigName(file);
            ConfigPtr config = getConfig(name);
            if (_paths[name] != current_timestamp) {
                _paths[name] = current_timestamp;
                config->setTimestamp(current_timestamp);
                std::cout << "Config file '" << name << "' has been modified" << std::endl;
                status = FileStatus::modified;
                config->update(status);
                _onChangeCallback();
            }
        }
    }
}

void ConfigManager::watching(const bool &watching)
{
    _watching = watching;
}

const bool ConfigManager::isWatching() const noexcept
{
    return _watching;
}

void ConfigManager::loadConfigDir(const std::string &path)
{
    for (const auto &file : std::filesystem::recursive_directory_iterator(path)) {
        std::string name = getConfigName(file);
        ConfigPtr config = ConfigPtr(new Config(file, name));
        _configs.push_back(std::move(config));
        _paths[name] = std::filesystem::last_write_time(file);
    }
}

void ConfigManager::setConfigPath(const std::string &path)
{
    _path = path;
}

const std::string ConfigManager::getConfigPath() const noexcept
{
    return _path;
}

void ConfigManager::setTimeToSleep(const TimeSleep &timeSleep)
{
    _timeSleep = timeSleep;
}

const TimeSleep ConfigManager::getTimeToSleep() const noexcept
{
    return _timeSleep;
}

void ConfigManager::onConfigChange(CallbackHandler &&handler)
{
    _onChangeCallback = std::move(handler);
}

void ConfigManager::onConfigErased(CallbackHandler &&handler)
{
    _onErasedCallback = std::move(handler);
}

ConfigPtr ConfigManager::getConfig(const std::string &config_name) const
{
    for (const auto &config : _configs)
        if (!config->getName().compare(config_name))
            return config;
    return nullptr;
}

const std::string ConfigManager::getConfigName(const FileDescriptor &file) const
{
    std::string filename = std::filesystem::path(
        file.path().string()).filename();
    std::size_t last_index = filename.find_last_of(".");
    const std::string name = filename.substr(0, last_index);

    return name;
}