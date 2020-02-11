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
#include <string>

#include "FileWatcher.hpp"
#include "SharedMemory.hpp"

#include <nlohmann/json.hpp>

namespace cfg {

	using json = nlohmann::json;

	class Config {
		public:
			Config(const std::filesystem::directory_entry &file);
			~Config() = default;

			void loadConfig(const std::filesystem::path &);

			void update();

			void setName(const std::string &);
			std::string getName() const noexcept;

			void setPath(const std::filesystem::path &);
			std::filesystem::path getPath() const noexcept;

			std::filesystem::file_time_type getTimestamp() const noexcept;

		private:
			std::string _name;
			std::filesystem::path _path;
			std::filesystem::file_time_type _timestamp;
			FileWatcher _fw;
			bool _reload;
			bool _running;

			key_t _key;
			int _shmid;
	};
}; // namespace cfg