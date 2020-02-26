/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** ServerConfig
*/

#include "ServerConfig.hpp"

using namespace Zia;

ServerConfig::ServerConfig(const FileDescriptor &file, const std::string &name):
    Config(file, name)
{
}

void ServerConfig::loadConfig(const std::filesystem::path &path)
{
    std::cout << "ServerConfig::loadConfig" << std::endl;
    std::ifstream file(path);
    json j;
    file >> j;
    file.close();
    _enabledModules.clear();
    // Load each attributes...
    try
    {
        std::string modules_path(std::getenv("MODULES_PATH"));
        for (auto &[key, value] : j["modules"].items()) {
            std::stringstream ss;
            ss << modules_path << std::string(value["module"]);

            std::filesystem::directory_entry de;
            std::filesystem::path config_path(ss.str());
            de.assign(config_path);
            auto module = std::shared_ptr<Module>(new Module(de));
            _enabledModules.emplace(std::move(module));
        }
    } catch(const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    updateEnabledModulesList();
}

void ServerConfig::updateEnabledModulesList()
{
    for (const auto &file : std::filesystem::recursive_directory_iterator(std::getenv("TMP_MODULES_PATH"))) {
        std::string name = getModuleName(file);
        bool is_enabled = false;
        for (auto &module : _enabledModules) {
            if (module->getName().compare(name) == 0) {
                is_enabled = true;
                break;
            }
        }
        if (is_enabled == false) {
            std::cout << "Remove not enabled module" << std::endl;
            std::filesystem::remove(file.path());
        }
    }
}

const EnabledList ServerConfig::getEnabledModulesList() const noexcept
{
    return _enabledModules;
}

const std::string ServerConfig::getModuleName(const std::string &filename) const
{
    std::size_t last_index = filename.find_last_of(".");
    const std::string name = filename.substr(0, last_index);
    return name;
}

const std::string ServerConfig::getModuleName(const FileDescriptor &file) const
{
    std::string filename = std::filesystem::path(
                               file.path().string())
                               .filename();
    std::size_t last_index = filename.find_last_of(".");
    const std::string name = filename.substr(0, last_index);
    return name;
}