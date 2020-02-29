/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** ServerConfig
*/

#include "ServerConfig.hpp"

using namespace Zia;

ServerConfig::ServerConfig(const FileDescriptor &file, const std::string &name):
    Config(file, name),
    _address(DefaultIP),
    _port(DefaultPort)
{
    loadConfig(file.path());
}

void ServerConfig::loadConfig(const std::filesystem::path &path)
{
    tls::JsonLoader jld(path);
    _enabledModules.clear();

    try {
        loadWebServices(jld.get("web_services"));
        loadModules(jld.get("modules"));
        _configPath = jld.get("config_path");
        _modulesPath = jld.get("modules_path");
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

const std::string ServerConfig::getAddress() const noexcept
{
    return _address;
}

const int ServerConfig::getPort() const noexcept
{
    return _port;
}

std::string ServerConfig::getConfigPath() const noexcept
{
    return _configPath;
}

std::string ServerConfig::getModulesPath() const noexcept
{
    return _modulesPath;
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

void ServerConfig::loadModules(const json &object)
{
    for (auto &[key, value] : object.items()) {
        std::stringstream ss;
        tls::JsonLoader jld(value);

        ss << tls::EnvManager::getEnv("MODULES_PATH") << std::string(jld.get("module"));

        std::filesystem::directory_entry de;
        std::filesystem::path config_path(ss.str());
        de.assign(config_path);
        auto module = std::shared_ptr<Module>(new Module(de));
        _enabledModules.emplace(std::move(module));
    }
}

void ServerConfig::loadWebServices(const json &object)
{
    tls::JsonLoader jld(object);

    _address = jld.get("address");
    _port = jld.get("port");
}