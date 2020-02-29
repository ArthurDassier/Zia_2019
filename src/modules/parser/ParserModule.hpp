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
    /**
     * @brief Enum for the HTTP methods
     */
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

    /**
     * @brief Enum between HTTP method and the api definds
     */
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

/**
 * @brief Parser class to manage the parser module.
 */
class Parser : public oZ::IModule {
public:
    /**
     * @brief Default constructor for the parset module
     */
    Parser() = default;

    /**
     * @brief Get the name of the module
     * 
     * @return The name of the module
     */
    virtual const char *getName(void) const { return "ParserModule"; }

    /**
     * @brief Fct for the pipeline (load in the right place in the right position)
     * 
     * @param pipeline Reference on the pipeline where the module is load
     */
    virtual void onRegisterCallbacks(oZ::Pipeline &pipeline);

private:
    /**
     * @brief Parse the browser's request and modify the context
     * 
     * @param context Context given by the pipeline
     * 
     * @return Bool to know if nothing wrong happened
     */
    bool parsing(oZ::Context &context);

};
