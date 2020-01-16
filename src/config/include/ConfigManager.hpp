/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** ConfigManager
*/

#pragma once

#include <unordered_map>

#include "Config.hpp"

class ConfigManager {
	public:
		ConfigManager();
		~ConfigManager();

		Config getConfig(const std::string &) const;

	private:
		std::unordered_map<std::string, Config> _configs;
};