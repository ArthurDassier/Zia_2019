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
        return false;

    std::string path = context.getRequest().getURI();
    std::string targetedFile;

    //permets de prendre plus que le text/html ->faire le parser apres le .
    //Faut split pour si jamais ?
    context.getResponse().getHeader().set("Content-Type", "text/html");
    if (FillModule::routes_enums[path] != "") {
        targetedFile = HTML_FILES_POSI + FillModule::routes_enums[path];
    } else {
        targetedFile = HTML_FILE_ERROR;
        fillBody(context, targetedFile, oZ::HTTP::Code::NotFound);
        return false;
    }
    fillBody(context, targetedFile, oZ::HTTP::Code::OK);
    return true;
}

bool Fill::checkRequestType(const oZ::Context &context)
{
    switch (context.getRequest().getMethod()) {
        case oZ::HTTP::Method::Get:
        case oZ::HTTP::Method::Post:
            return true;
        default:
            return false;
    }
    return false;
}

bool Fill::fillBody(oZ::Context &context, const std::string &path, oZ::HTTP::Code code)
{
    switch (code)
    {
    case oZ::HTTP::Code::OK:
        context.getResponse().getReason() = "Ok";
        break;
    case oZ::HTTP::Code::NotFound:
        context.getResponse().getReason() = "Not found";
        break;
    default:
        context.getResponse().getReason() = "Not found";
        break;
    }
    context.getResponse().setCode(code);
    std::ifstream is(path.c_str(), std::ios::in | std::ios::binary);
    char buf[512];
    std::string content;
    while (is.read(buf, sizeof(buf)).gcount() > 0)
        content.append(buf, is.gcount());
    context.getResponse().getBody() = content;
    context.getResponse().getHeader().set("Content-Length", std::to_string(content.size()));
    return true;
}