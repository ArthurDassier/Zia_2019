/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** EnvManager
*/

#include "EnvManager.hpp"

using namespace tls;

EnvManager::EnvManager():
    _cwd(std::filesystem::current_path().string()),
    _config_path("config/config.json")
{
}

EnvManager::EnvManager(const std::filesystem::path &config_path):
    _cwd(std::filesystem::current_path().string()),
    _loader(config_path),
    _config_path(config_path)
{
}

void EnvManager::setEnv(const std::string &name, const std::string &value)
{
    std::cout << "setenv(" << name << ", " << value << ", 1);" << std::endl;
    setenv(name.c_str(), value.c_str(), 1);
}

const std::string EnvManager::getEnv(const std::string &name)
{
    auto env = std::getenv(name.c_str());
    if (!env) {
        std::cerr << "EnvManager [Error]: " << name << " does not exists" << std::endl;
        return "";
    }
    return env;
}

void EnvManager::loadEnv(const std::filesystem::path &config_path)
{      
    if (!_loader.hasLoaded())
        _loader.load(config_path);

    json env_vars = _loader.get("env_variables");
    if (env_vars.is_null())
        return;
    for (auto &[key, array] : env_vars.items()) {
        for (auto &[name, value] : array.items()) {
            std::stringstream ss;
            ss << _cwd << std::string(value);
            setEnv(name, ss.str());
        }
    }
}