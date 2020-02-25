/*
** EPITECH PROJECT, 2020
** Parser.cpp
** File description:
** fill
*/

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include "FillPage.hpp"

OPEN_ZIA_MAKE_ENTRY_POINT(Fill)

void Fill::onRegisterCallbacks(oZ::Pipeline &pipeline)
{
    std::cout << "=> FillPage" << std::endl;
    pipeline.registerCallback(
        oZ::State::Interpret,
        oZ::Priority::ASAP,
        this, &Fill::takeContent
    );
}

bool Fill::takeContent(oZ::Context &context)
{
    if (checkRequestType(context) == false)
        return true;

    std::string path = context.getRequest().getURI();
    std::string targetedFile;

    if (FillModule::routes_enums[path] != "") {
        context.getResponse().getHeader().set("Content-Type", "text/html");
        targetedFile = HTML_FILES_POSI + FillModule::routes_enums[path];
    }

    std::ifstream is(targetedFile.c_str(), std::ios::in | std::ios::binary);
    if (!is) {
        context.getResponse().getReason() = "Not found";
        context.getResponse().setCode(oZ::HTTP::Code::NotFound);
        return true;
    }
    context.getResponse().getReason() = "Ok";
    context.getResponse().setCode(oZ::HTTP::Code::OK);

    char buf[512];
    std::string content;
    while (is.read(buf, sizeof(buf)).gcount() > 0)
        content.append(buf, is.gcount());
    context.getResponse().getBody() = content;
    context.getResponse().getHeader().set("Content-Length", std::to_string(content.size()));
    return true;
}

bool Fill::checkRequestType(const oZ::Context &context)
{
    return (context.getRequest().getMethod() == oZ::HTTP::Method::Get);
}