/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** JsonLoader
*/

#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

namespace tls
{
    /**
     * @brief Json library object.
     */
    using json = nlohmann::json;

    /**
     * @brief JsonLoader class to manage a json file
     */
    class JsonLoader
    {
        public:
            /**
             * @brief Construct a new JsonLoader object.
             */
            JsonLoader();

            /**
             * @brief Construct a new JsonLoader object.
             * 
             * @param path Path of the json file to load.
             */
            JsonLoader(const std::filesystem::path &path);

            /**
             * @brief Destroy the JsonLoader object.
             */
            ~JsonLoader() = default;

            /**
             * @brief Load a json from a given json file.
             * 
             * @param path Path of the json file to load.
             */
            void load(const std::filesystem::path &path);

            /**
             * @brief Get data from the json previously loaded.
             * 
             * @param to_get Data key in the json.
             * 
             * @return Data if found otherwise null json object.
             */
            [[nodiscard]] const json get(const std::string &to_get) const;

            /**
             * @brief Get all json file content deserialized.
             * 
             * @return Json object.
             */
            [[nodiscard]] const json getJson() const noexcept;

            /**
             * @brief Check if a json file has already been loaded.
             * 
             * @return True if a file has been loaded otherwise false.
             */
            [[nodiscard]] const bool hasLoaded() const noexcept;

        private:
            json _json;
            bool _hasLoaded;
    };
}; // namespace tls