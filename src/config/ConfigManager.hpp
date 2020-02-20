/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** ConfigManager
*/

#pragma once

#include <cstdlib>
#include <functional>
#include <memory>
// #include <pair>
#include <unordered_map>
#include <vector>

#include "Config.hpp"

namespace cfg
{
	typedef std::pair<Config *, std::thread *> config_t;
	class ConfigManager
	{
		public:
			using CallbackHandler = std::function<bool()>;

			using ThreadPtr = std::shared_ptr<std::thread>;

			using ThreadedConfig = std::pair<ConfigPtr, ThreadPtr>;

			using FileDescriptor = std::filesystem::directory_entry;

			using ConfigList = std::vector<ThreadedConfig>;

			ConfigManager(const std::string &path);

			virtual ~ConfigManager() = default;

			void manage();
			void stop();

			void loadConfigDir();

			void setConfigPath(const std::string &path);

			[[nodiscard]] const std::string getConfigPath() const noexcept;

			// void setCallback(const);

			[[nodiscard]] ConfigPtr getConfig(const std::string &configName) const;

		private:
			std::string _path;
			ConfigList _configs;

			[[nodiscard]] const std::string getConfigName(const FileDescriptor &file) const;
	};
}; // namespace cfg