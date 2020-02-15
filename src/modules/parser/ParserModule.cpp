/*
** EPITECH PROJECT, 2020
** Parser.cpp
** File description:
** Parser
*/

#include <string>
#include <sstream>
#include <iostream>
#include "ParserModule.hpp"

extern "C" oZ::ModulePtr CreateModule(void) { return std::make_shared<ParserModule>(); }

void ParserModule::onRegisterCallbacks(oZ::Pipeline &pipeline)
{
    std::cout << "TEST 1" << std::endl;
    pipeline.registerCallback(
        oZ::State::Parse,
        oZ::Priority::ASAP,
        this, &ParserModule::Launch
    );
}

bool ParserModule::Launch(oZ::Context &context)
{
    std::string data(
        context.getPacket().getByteArray().begin(),
        context.getPacket().getByteArray().end());

    /* Method */
    std::string temp(data);
    std::string method(temp.substr(0, temp.find(" ")));
    std::cout << "LA BITE A GRIVEAUX" << std::endl;
    if (std::find(  ParserModuleHTTP::methods.begin(),
                    ParserModuleHTTP::methods.end(),
                    method) != ParserModuleHTTP::methods.end())
        context.getRequest().setMethod(ParserModuleHTTP::methods_enums[method]);
    else
        return false;

    temp = temp.substr(temp.find(" ") + 1);

    /* URI */
    std::string uri(temp.substr(0, temp.find(" ")));
    if (uri.size() <= 0)
        return false;
    context.getRequest().getURI() = uri;

    temp = temp.substr(temp.find(" ") + 1);

    /* Version */
    oZ::HTTP::Version v;
    temp = temp.substr(temp.find("/") + 1);
    std::string version(temp.substr(0, temp.find("\n")));
    v.majorVersion = std::stoi(version.substr(0, version.find(".")));
    version.substr(1);
    v.minorVersion = std::stoi(version);
    context.getRequest().setVersion(v);

    /* Header */
    std::string line;
    std::stringstream tempstream(temp);
    std::getline(tempstream, line);
    while (std::getline(tempstream, line)) {
        context.getRequest().getHeader().set(
            line.substr(0, line.find(":")),
            line.substr(line.find(" ") + 1));
    }

    return true;
}