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

class Fill : public oZ::IModule {
public:
    Fill() = default;

    virtual const char *getName(void) const { return "TestModule"; }

    virtual void onRegisterCallbacks(oZ::Pipeline &pipeline);

private:
    bool takeContent(oZ::Context &context);
    bool checkRequestType(const oZ::Context &context);

};
