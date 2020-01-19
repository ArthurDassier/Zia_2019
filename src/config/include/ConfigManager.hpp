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

namespace cfg {
	class ConfigManager {
		public:
			ConfigManager(const std::string &);
			~ConfigManager();

			void 	manage();

			void	setConfigPath(const std::string &);
			Config	*getConfig(const std::string &);

		private:
			std::unordered_map<std::string, Config*> _configs;
	};
}; // namespace cfg