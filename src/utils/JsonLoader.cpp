/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** JsonLoader
*/

#include "JsonLoader.hpp"

using namespace tls;

JsonLoader::JsonLoader():
    _hasLoaded(false)
{
}

JsonLoader::JsonLoader(const std::filesystem::path &path):
    _hasLoaded(false)
{
    load(path);
}

void JsonLoader::load(const std::filesystem::path &path)
{
    std::ifstream file(path);
    file >> _json;
    file.close();
    _hasLoaded = true;
}

const json JsonLoader::get(const std::string &to_get) const
{
    json j;

    try {
        j = _json[to_get];
    } catch (const std::exception &e) {
        std::cerr << "JsonLoader [Error]: " << e.what() << std::endl;
    }
    return j;
}

    const json JsonLoader::getJson() const noexcept
{
    return _json;
}

const bool JsonLoader::hasLoaded() const noexcept
{
    return _hasLoaded;
}