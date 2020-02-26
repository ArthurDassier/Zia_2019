/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** 
*/

#include "php_module.hpp"
// #include <stdlib.h>
#include <cstdlib>

OPEN_ZIA_MAKE_ENTRY_POINT(PHP_CGI)

void PHP_CGI::onRegisterCallbacks(oZ::Pipeline &pipeline)
{
    std::cout << "=> PHP_CGI" << std::endl;
    pipeline.registerCallback(
        oZ::State::AfterInterpret,
        oZ::Priority::ASAP,
        this, &PHP_CGI::execPHP
    );
}

const char **PHP_CGI::makeEnvironment(const oZ::Context &context)
{
    std::map<std::string, std::string> env;
    // Faire l'env pour que l'on foute la query string dedans
    // env["PATH"] = std::getenv("PATH");
    // env["REMOTE_ADDR"] = context.getPacket().getEndpoint().getAddress();
    // env["REMOTE_PORT"] = context.getPacket().getEndpoint().getPort();
    // env["REDIRECT_STATUS"] = 200;
    // env["CONTENT_LENGTH"] = 6;
    // env["PATHEXT"] = ".FRR";
    // if (context.getRequest().getMethod() == oZ::HTTP::Method::Get) {
    //     env["REQUEST_METHOD"] = "GET";
    // } else if (context.getRequest().getMethod() == oZ::HTTP::Method::Post) {
    // env["REQUEST_METHOD"] = "POST";
    // }
    // env["GATEWAY_INTERFACE"] = "CGI/1.1";
    // env["REQUEST_URI"] = context.getRequest().getURI();
    std::cout << "TATA" << std::endl;
    try
    {
        env["SCRIPT_FILENAME"] = 
        env["QUERY_STRING"] = context.getRequest().getHeader().get("bodyPost").c_str();
        // std::cout << "QUERY_STRING=" << env["QUERY_STRING"] << std::endl;
        // std::cout << "Envrionment has been sent : " << env["QUERY_STRING"] << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    size_t i = 0;
    const char **e = new const char *[env.size() + 1];
    for (auto it = env.begin(); it != env.end(); ++it)
    {
        std::string s = it->first + "=" + it->second;
        int size = s.size();
        char *buff = new char[size + 1];
        s.copy(buff, size);
        buff[size] = '\0';
        e[i] = buff;
        i = i + 1;
    }
    // std::cout << "ENV[0] ==" << e[0] << std::endl;
    e[i] = NULL;
    return e;
}

bool PHP_CGI::execPHP(oZ::Context &context)
{
    int pipefd[2];
    pid_t pid;

    if (!findPHP(context))
        return true;
    if (pipe(pipefd) == -1) {
        std::cout << "PHPModule: error in pipe" << std::endl;
        return true;
    }

    char tmpPath[] = "/tmp/tmpPhpExec.XXXXXX";
    int fd;
    if ((fd = mkstemp(tmpPath)) == -1) {
        std::cout << "PHPModule: error in mkstemp" << std::endl;
        return true;
    }
    // std::cout << context.getResponse().getBody().c_str() << std::endl;
    write(fd, context.getResponse().getBody().c_str(), context.getResponse().getBody().size());

    pid = fork();
    if (pid == -1) {
        std::cout << "PHPModule: error in fork" << std::endl;
        return true;
    }

    char *tmpArgv[] = {(char *)"/usr/bin/php-cgi", (char *)tmpPath, NULL};
    const char **env = this->makeEnvironment(context);
    if (pid == 0) {
        close(pipefd[0]);
        if (dup2(pipefd[1], 1) == -1)
            exit(84);
        int rc = execve(tmpArgv[0], &tmpArgv[0], const_cast<char *const *>(env));
        _exit(rc);
    } else {
        close(pipefd[1]);
        int exitCode = 0;
        waitpid(pid, &exitCode, 0);
        if (exitCode != 0) {
            std::cout << "PHPModule: error in execve" << std::endl;
            return true;
        }
        close(fd);
        unlink(tmpPath);
        int r = -1;
        char buff[128];
        std::string content;
        while ((r = read(pipefd[0], buff, 128)) != -1 && r > 0)
            content.append(buff, r);
        close(pipefd[0]);
        if (r == -1) {
            std::cout << "PHPModule: can't read the result" << std::endl;
            return true;
        }
        content = content.substr(content.find("<"));
        context.getResponse().getBody() = content;
        context.getResponse().getHeader().get("Content-Length") = std::to_string(content.size());
        return true;
    }
    return true;
}

bool PHP_CGI::findPHP(const oZ::Context &context)
{
    std::string path(HTML_FILES_POSI + PHPModule::routes_enums[context.getRequest().getURI()]);
    std::ifstream is(path.c_str(), std::ios::in | std::ios::binary);
    char buf[512];
    std::string content;

    if (!is.is_open()) {
        std::cout << "PHP: Can't open the file" << std::endl;
        return false;
    }
    while (is.read(buf, sizeof(buf)).gcount() > 0)
        content.append(buf, is.gcount());
    is.close();
    if (content.find("<?php") != std::string::npos)
        return true;
    return false;
}