#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main() {

    std::string line;
    std::ifstream myfile("config/config.json");
    json j;

    myfile >> j;

    auto j2 = j["web_services"];
    for (auto const &it : j2)
        std::cout << it << std::endl;

    // std::ofstream o("pretty.json");
    // o << std::setw(4) << j << std::endl;

    // j["pi"] = 3.141;
    // j["happy"] = true;
    // j["name"] = "Niels";
    // j["nothing"] = nullptr;
    // j["answer"]["everything"] = 42;
    // j["list"] = {1, 0, 2};
    // j["object"] = {{"currency", "USD"}, {"value", 42.99}};

    for (auto const &it : j)
        std::cout << it << std::endl;
}