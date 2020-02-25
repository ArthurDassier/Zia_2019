/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** Config
*/

#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>

#include "FileWatcher.hpp"

namespace cfg
{
	class Config;

	/**
	 * @brief Config pointer type, using shared_ptr as backend.
	 */
	using ConfigPtr = std::shared_ptr<Config>;

	/**
	 * @brief File descriptor from a directory entry.
	 */
	using FileDescriptor = std::filesystem::directory_entry;

	/**
	 * @brief File last modified date.
	 */
	using Timestamp = std::filesystem::file_time_type;

	/**
	 * @brief Json library object.
	 */
	using json = nlohmann::json;

	class Config
	{
		public:
			Config(const FileDescriptor &file, const std::string &path);
			~Config() = default;

			// Virtual function to inherit
			void loadConfig(const std::filesystem::path &path);
			// virtual void loadConfig(const std::filesystem::path &path) = 0;

			void update(const FileStatus &status);

			void setName(const std::string &name);
			[[nodiscard]] const std::string getName() const noexcept;

			void setPath(const std::filesystem::path &path);
			[[nodiscard]] std::filesystem::path getPath() const noexcept;

			void setTimestamp(const Timestamp &timestamp);
			[[nodiscard]] Timestamp getTimestamp() const noexcept;

		private:
			std::string _name;
			std::filesystem::path _path;
			Timestamp _timestamp;
	};
}; // namespace cfg