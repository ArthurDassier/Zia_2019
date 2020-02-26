/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** Module
*/

#pragma once

#include <config/Config.hpp>

namespace Zia
{
    class Module
    {
        public:
            /**
             * @brief Construct a new Module object.
             * 
             * @param path File descriptor of the module library.
             */
            Module(const cfg::FileDescriptor &path);

            /**
             * @brief Destroy the Module object.
             */
            ~Module() = default;

            /**
             * @brief Get the module's name.
             * 
             * @return Module's name.
             */
            [[nodiscard]] const std::string getName() const noexcept;

            /**
             * @brief Generate the module's name from a file descriptor.
             * 
             * @return Generated module name.
             */
            [[nodiscard]] const std::string getName(const cfg::FileDescriptor &file) const;

            /**
             * @brief Get the module's library path.
             * 
             * @return Module's library path.
             */
            [[nodiscard]] const std::string getPath() const noexcept;

        private:
            std::string _name;
            std::string _path;
    };
}; // namespace Zia