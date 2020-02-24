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

OPEN_ZIA_MAKE_ENTRY_POINT(Parser)

void Parser::onRegisterCallbacks(oZ::Pipeline &pipeline)
{
    std::cout << "=> onRegisterCallbacks" << std::endl;
    pipeline.registerCallback(
        oZ::State::Parse,
        oZ::Priority::ASAP,
        this, &Parser::Launch
    );
}

bool Parser::Launch(oZ::Context &context)
{
    std::cout << "=> Launch" << std::endl;
    std::string data(
        context.getPacket().getByteArray().begin(),
        context.getPacket().getByteArray().end());

    /* Method */
    std::string temp(data);
    std::string method(temp.substr(0, temp.find(" ")));

    if (std::find(  ParserModule::methods.begin(),
                    ParserModule::methods.end(),
                    method) != ParserModule::methods.end())
        context.getRequest().setMethod(ParserModule::methods_enums[method]);
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
    context.getResponse().setVersion(v);

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