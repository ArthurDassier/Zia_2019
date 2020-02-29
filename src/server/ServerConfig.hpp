/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** ServerConfig
*/

#pragma once

#include <set>
#include <vector>

#include <config/Config.hpp>
#include <openZia/IModule.hpp>
#include <utils/EnvManager.hpp>
#include <utils/JsonLoader.hpp>

#include "Module.hpp"

using namespace cfg;

namespace Zia
{
    /**
     * @brief Default HTTP port
     */
    const int DefaultPort = 80;

    /**
     * @brief Default HTTPS port
     */
    const int DefaultPortHTTPS = 443;

    /**
     * @brief Default IP address
     */
    const std::string DefaultIP = "127.0.0.1";

    /**
     * @brief Module pointer type, using shared_ptr as backend.
     */
    using ModulePtr = std::shared_ptr<Module>;

    /**
     * @brief Set containing ModulePtr modules.
     */
    using EnabledList = std::set<ModulePtr>;

    /**
     * @brief ServerConfig class to manage configuration files of the server.
     */
    class ServerConfig : virtual public Config
    {
        public:
            /**
             * @brief Construct a new ServerConfig object.
             * 
             * @param file File descriptor of the associated json configuration file.
             * @param name Registration name of the ServerConfig object.
             */
            ServerConfig(const FileDescriptor &file, const std::string &name);

            /**
             * @brief Destroy the ServerConfig object.
             */
            ~ServerConfig() = default;

            /**
             * @brief Load configuration from a given file.
             * 
             * @param path Path to the configuration file.
             */
            void loadConfig(const std::filesystem::path &path);

            /**
             * @brief Update list of enabled modules.
             */
            void updateEnabledModulesList();

            [[nodiscard]] const std::string getAddress() const noexcept;

            [[nodiscard]] const int getPort() const noexcept;

            [[nodiscard]] std::string getConfigPath() const noexcept;

            [[nodiscard]] std::string getModulesPath() const noexcept;

            /**
             * @brief Get list of enabled modules.
             * 
             * @return List of enabled modules as EnabledList type.
             */
            [[nodiscard]] const EnabledList getEnabledModulesList() const noexcept;

            /**
             * @brief
             */
            const std::string getModuleName(const std::string &filename) const;

            /**
             * @brief
             */
            const std::string getModuleName(const FileDescriptor &file) const;

        private:
            std::string _address;
            int _port;
            std::string _configPath;
            std::string _modulesPath;
            EnabledList _enabledModules;
            // tls::EnvManager _envManager;

            /**
             * @brief
             */
            void loadModules(const json &object);

            /**
             * @brief
             */
            void loadWebServices(const json &object);
    };
}; // namespace Zia