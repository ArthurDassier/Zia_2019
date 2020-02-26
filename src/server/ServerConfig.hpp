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

#include "Module.hpp"

using namespace cfg;

namespace Zia
{
    /**
     * @brief Module pointer type, using shared_ptr as backend.
     */
    using ModulePtr = std::shared_ptr<Module>;

    /**
     * @brief Set containing ModulePtr modules.
     */
    using EnabledList = std::set<ModulePtr>;

    /**
     * @brief Class to manage configuration files of the server.
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
            EnabledList _enabledModules;
    };
}; // namespace Zia