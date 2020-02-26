/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** FillPage
*/

#pragma once

#include <openZia/IModule.hpp>
#include <openZia/Pipeline.hpp>
#include <map>

#define HTML_FILES_POSI "src/HTML/"
#define HTML_FILE_ERROR "src/HTML/404.html"

namespace FillModule
{
    std::map<std::string, std::string> routes_enums = {
        {"/",      "index.html"},
        {"/test",  "index_test.html"},
        {"/php",   "index_php.html"},
        {"/form",  "index_form.html"}
    };
}

class Fill : public oZ::IModule {
    public:
        Fill() = default;

        virtual const char *getName(void) const { return "FillPageModule"; }

        virtual void onRegisterCallbacks(oZ::Pipeline &pipeline);

    private:
        bool takeContent(oZ::Context &context);
        bool checkRequestType(const oZ::Context &context);
        bool fillBody(oZ::Context &context, const std::string &path, oZ::HTTP::Code code);

};
