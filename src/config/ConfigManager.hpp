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
#include <unordered_map>
#include <vector>

#include "Config.hpp"

namespace cfg
{
	/**
	 * @brief Simple time unit of measuring.
	 */
	using TimeSleep = std::chrono::milliseconds;

	/**
	 * @brief Class to manage the configuration files.
	 */
	class ConfigManager
	{
		public:
			/**
			 * @brief Callback handler that stores something's callback function.
			 */
			using CallbackHandler = std::function<void()>;

			/**
			 * @brief Thread pointer type, using shared_ptr as backend.
			 */
			using ThreadPtr = std::shared_ptr<std::thread>;

			/**
			 * @brief Vector containing IConfig modules.
			 */
			using ConfigList = std::vector<ConfigPtr>;

			/**
			 * @brief Unordered_map containing IConfig modules as key and config file timestamp.
			 */
			using ConfigMap = std::unordered_map<std::string, Timestamp>;

			/**
			 * @brief Construct a new ConfigManager object.
			 * 
			 * @param path Path to the directory containing configurations files to watch.
			 */
			ConfigManager(const std::string &path);

			/**
			 * @brief Construct a new ConfigManager object.
			 */
			ConfigManager();

			/**
			 * @brief Destroy the ConfigManager object.
			 */
			virtual ~ConfigManager() = default;

			/**
			 * @brief Set watching variable to true and run watch method in a detached thread.
			 */
			void manage();

			/**
			 * @brief Stop watch method and join the detached thread.
			 */
			void stop();

			/**
			 * @brief Check every X milliseconds for a modification in the configuration path.
			 * 
			 *  - If a file is modified, matching config will be reloaded.
			 *  - If a file is deleted, matching config will be removed from the ConfigList.
			 */
			void watch();

			/**
			 * @brief Set watching attribute.
			 * 
			 * @param watching Boolean.
			 */
			void watching(const bool &watching);

			/**
			 * @brief Get watching attribute.
			 * 
			 * @return Watching attribute as a boolean.
			 */
			[[nodiscard]] const bool isWatching() const noexcept;

			/**
			 * @brief Load all configuration file from a given path.
			 * 
			 * @param path Path where to load the configuration files.
			 */
			void loadConfigDir(const std::string &path);

			/**
			 * @brief Callback called when a file has been modified.
			 * 
			 * @param handler Callback function.
			 */
			void onConfigChange(CallbackHandler &&handler);

			/**
			 * @brief Callback called when a file has been erased.
			 * 
			 * @param handler Callback function
			 */
			void onConfigErased(CallbackHandler &&handler);

			/**
			 * @brief Set the configuration path.
			 * 
			 * @param path Path where the configuration files are.
			 */
			void setConfigPath(const std::string &path);

			/**
			 * @brief Get the configuration path.
			 * 
			 * @return The configuration path as a std::string.
			 */
			[[nodiscard]] const std::string getConfigPath() const noexcept;

			/**
			 * @brief Set the time to sleep between each watch loop.
			 * 
			 * @param timeSleep Time to sleep in milliseconds.
			 */
			void setTimeToSleep(const TimeSleep &timeSleep);

			/**
			 * @brief Get the time to sleep between each watch loop.
			 * 
			 * @return The time to sleep as a TimeSleep.
			 */
			[[nodiscard]] const TimeSleep getTimeToSleep() const noexcept;

			/**
			 * @brief Get Config object from the loaded configs.
			 * 
			 * @param configName Name of the Config object wanted.
			 * 
			 * @return Wanted ConfigPtr.
			 */
			[[nodiscard]] ConfigPtr getConfig(const std::string &configName) const;

		private:
			std::string _path;
			TimeSleep _timeSleep;
			
			ConfigList _configs;
			ConfigMap _paths;

			CallbackHandler _onChangeCallback;
			CallbackHandler _onErasedCallback;
			
			ThreadPtr _thread;
			bool _watching;

			/**
			 * @brief Generate a configuration name from a given file.
			 * 
			 * @return Name of the configuration as a std::string.
			 */
			[[nodiscard]] const std::string getConfigName(const FileDescriptor &file) const;
	};
}; // namespace cfg