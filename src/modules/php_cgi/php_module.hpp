/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** PHP
*/

#pragma once

#include <openZia/IModule.hpp>
#include <openZia/Pipeline.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <iostream>
#include <fstream>
#include <map>

#define HTML_FILES_POSI "src/HTML/"

namespace PHPModule
{
    std::map<std::string, std::string> routes_enums = {
        {"/",      "index.html"},
        {"/test",  "index_test.html"},
        {"/php",   "index_php.html"}
    };
}

class PHP_CGI : public oZ::IModule 
{
    public:
        PHP_CGI() = default;

        virtual const char *getName(void) const { return "PHPModule"; }

        virtual void onRegisterCallbacks(oZ::Pipeline &pipeline);

    private:
        bool execPHP(oZ::Context &context);
        bool findPHP(const oZ::Context &context);
        const char **makeEnvironment(const oZ::Context &context);

};
