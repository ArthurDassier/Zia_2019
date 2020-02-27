/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** EnvManager
*/

#pragma once

#include <iostream>

#include "JsonLoader.hpp"

namespace tls
{
    /**
     * @brief EnvManager class to manage environment variables
     */
    class EnvManager
    {
        public:
            /**
             * @brief Construct a new EnvManager object.
             */
            EnvManager();

            /**
             * @brief Construct a new EnvManager object.
             * 
             * @param config_path Path to a json configuration file.
             */
            EnvManager(const std::filesystem::path &config_path);

            /**
             * @brief Destroy the EnvManager object.
             */
            ~EnvManager() = default;

            /**
             * @brief Set an environment variable.
             * 
             * @param name Name of the variable.
             * @param value Value of the variable.
             */
            void setEnv(const std::string &name, const std::string &value);

            /**
             * @brief Get an environment variable.
             * 
             * @param name Name of the variable to retrieve.
             * 
             * @return Value of the found environment variable.
             */
            const std::string getEnv(const std::string &name) const;

            /**
             * @brief Set a list of environment variable from a json file.
             * 
             * @param config_path File where the environment variables are described.
             */
            void loadEnv(const std::filesystem::path &config_path = "");

        private:
            json _config;
            std::string _cwd;
            JsonLoader _loader;
            std::filesystem::path _config_path;
    };
}; // namespace tls