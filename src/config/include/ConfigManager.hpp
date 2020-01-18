/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** ConfigManager
*/

#pragma once

#include <cstdlib>
#include <memory>
#include <unordered_map>

#include "Config.hpp"

class ConfigManager {
	public:
		ConfigManager(const std::string &);
		~ConfigManager();

		void 	manage();

		void	setConfigPath(const std::string &);
		std::shared_ptr<Config>	getConfig(const std::string &);

		void 	setConfigDelay(const std::chrono::duration<int, std::milli>);

	private:
		std::unordered_map<std::string, Config*> _configs;
};