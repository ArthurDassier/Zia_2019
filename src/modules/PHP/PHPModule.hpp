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
    /**
     * @brief Enum for the server's routes with php
     */
    std::map<std::string, std::string> routes_enums = {
        {"/",      "index.html"},
        {"/test",  "index_test.html"},
        {"/php",   "index_php.html"},
        {"/form",  "index_form.html"}
    };
}

class PHP_CGI : public oZ::IModule 
{
    public:
        /**
         * @brief Default constructor for the php module
         */
        PHP_CGI() = default;

        /**
         * @brief Get the name of the module
         * 
         * @return The name of the module
         */
        virtual const char *getName(void) const { return "PHPModule"; }

        /**
         * @brief Fct for the pipeline (load in the right place in the right position)
         * 
         * @param pipeline Reference on the pipeline where the module is load
         */
        virtual void onRegisterCallbacks(oZ::Pipeline &pipeline);

    private:
        /**
         * @brief Execute the php find in the index and set the context
         * 
         * @param context Context given by the server
         * 
         * @return Bool to know if nothing wrong happened
         */
        bool execPHP(oZ::Context &context);

        /**
         * @brief Search if there's php in the context
         * 
         * @param context Context given by the server
         * 
         * @return True if php is find and false if not
         */
        bool findPHP(const oZ::Context &context);

        /**
         * @brief Create a temp env for exec the php
         * 
         * @param context Context given by the server
         * 
         * @return The env created
         */
        const char **makeEnvironment(const oZ::Context &context);
};
