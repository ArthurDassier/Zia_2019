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
#include <thread>

namespace cfg
{
	/**
	 * @brief Config object to retrieve the different configuration from a json file
	 */
	class Config;

	/**
	 * @brief File status enumeration.
	 */
	enum class FileStatus
    {
        created,
        modified,
        erased,
        none
    };

	/**
	 * @brief Operator to convert a FileStatus type to a std::ostream.
	 */
	static std::ostream& operator<<(std::ostream& os, FileStatus& fs)
    {
        switch (fs)
        {
            case FileStatus::created:   return os << "created";
            case FileStatus::modified:  return os << "modified";
            case FileStatus::erased:    return os << "erased";
            default:                    return os << "none";
        };
    }

	/**
	 * @brief Operator to convert a const char * type to a FileStatus.
	 */
	static FileStatus operator<<(FileStatus& s, const char *fs)
    {
        if (std::strcmp(fs, "created\n") == 0)  return s = FileStatus::created;
        if (std::strcmp(fs, "modified\n") == 0) return s = FileStatus::modified;
        if (std::strcmp(fs, "erased\n") == 0)   return s = FileStatus::erased;
        return s = FileStatus::none;
    }

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

	/**
	 * @brief Config abstracts a configuration from a json file.
	 */
	class Config
	{
		public:
			/**
			 * @brief Construct a new Config object.
			 * 
			 * @param file File descriptor of the associated json configuration file.
			 * @param name Registration name of the Config object.
			 */
			Config(const FileDescriptor &file, const std::string &name);

			/**
			 * @brief Destroy the Config object.
			 */
			virtual ~Config() = default;

			/**
			 * @brief Load configuration from a given file.
			 * 
			 * @param path Path to the configuration file.
			 */
			// Virtual function to inherit
			void loadConfig(const std::filesystem::path &path);
			// virtual void loadConfig(const std::filesystem::path &path) = 0;

			/**
			 * @brief 
			 */
			void update(const FileStatus &status);

			/**
			 * @brief Set the configuration's name.
			 * 
			 * @param name Name to set.
			 */
			void setName(const std::string &name);

			/**
			 * @brief Get the configuration's name.
			 */
			[[nodiscard]] const std::string getName() const noexcept;

			/**
			 * @brief Get the configuration's file descriptor.
			 */
			[[nodiscard]] const FileDescriptor getFileDescriptor() const noexcept;

			/**
			 * @brief Set the configuration's file path.
			 * 
			 * @param path Path to set.
			 */
			void setPath(const std::filesystem::path &path);

			/**
			 * @brief Get the configuration's file path.
			 */
			[[nodiscard]] std::filesystem::path getPath() const noexcept;

			/**
			 * @brief Set the configuration's timestamp.
			 * 
			 * @param timestamp Timestamp to set.
			 */
			void setTimestamp(const Timestamp &timestamp);

			/**
			 * @brief Get the configuration's timestamp.
			 */
			[[nodiscard]] Timestamp getTimestamp() const noexcept;

		private:
			std::string _name;
			FileDescriptor _fd;
			std::filesystem::path _path;
			Timestamp _timestamp;
	};
}; // namespace cfg