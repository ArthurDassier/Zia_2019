/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** Parser
*/

#pragma once

#include <openZia/IModule.hpp>
#include <openZia/Pipeline.hpp>
#include <map>

namespace ParserModule
{
    const std::vector<std::string> methods = {
        "GET",
        "HEAD",
        "POST",
        "PUT",
        "DELETE",
        "CONNECT",
        "OPTIONS",
        "TRACE"
    };

    std::map<std::string, oZ::HTTP::Method> methods_enums = {
        {"GET",     oZ::HTTP::Method::Get},
        {"HEAD",    oZ::HTTP::Method::Head},
        {"POST",    oZ::HTTP::Method::Post},
        {"PUT",     oZ::HTTP::Method::Put},
        {"DELETE",  oZ::HTTP::Method::Delete},
        {"CONNECT", oZ::HTTP::Method::Connect},
        {"OPTIONS", oZ::HTTP::Method::Option},
        {"TRACE",   oZ::HTTP::Method::Trace}
    };
}

class Parser : public oZ::IModule {
public:
    Parser() = default;

    virtual const char *getName(void) const { return "ParserModule"; }

    virtual void onRegisterCallbacks(oZ::Pipeline &pipeline);

private:
    bool Launch(oZ::Context &context);

};
