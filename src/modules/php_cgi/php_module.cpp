/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** 
*/

#include "php_module.hpp"

/*
int main(int argc, char **argv, char **env)
{
    int pipefd[2];
    pid_t pid;
    char buf;

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {                             // Le fils
        const char *bin = "/usr/bin/php-cgi";
        // const char *argv[] = {bin, NULL};    // commande pour lancer l'interpréteur
        close(pipefd[0]);                       // Ferme l'extrémité de lecture inutilisée
        if (dup2(pipefd[1], 1) == -1) {
            std::cout << "dup2 a echoue" << std::endl;
            exit(84);
        }

        //-f ou rien c un fichier, -r il faut exec la ligne direct
        int rc = execve(
            bin,
            const_cast<char * const *>(argv),
            const_cast<char * const *>(env)
            );

        _exit(rc);

    } else {
        close(pipefd[1]);
        int exitCode = 0;
        waitpid(pid, &exitCode, 0);
        if (exitCode != 0) {
            std::cout << "hum l'execve a pas marché" << std::endl;
            exit(84);
        }

        int r = -1;
        char buff[128];
        std::string content;
        while ((r = read(pipefd[0], buff, 128)) != -1 && r > 0)
            content.append(buff, r);
        close(pipefd[0]);
        if (r == -1) {
            std::cout << "hum pb de read" << std::endl;
            exit(84);
        }
        std::cout << "le content final: " << std::endl << content << std::endl;
    }
    return (0);
}
*/

OPEN_ZIA_MAKE_ENTRY_POINT(PHP_CGI)

void PHP_CGI::onRegisterCallbacks(oZ::Pipeline &pipeline)
{
    std::cout << "=> PHP_CGI" << std::endl;
    pipeline.registerCallback(
        oZ::State::Interpret,
        oZ::Priority::ASAP,
        this, &Fill::takeContent
    );
}

bool PHP_CGI::execPHP(oZ::Context &context)
{
    int pipefd[2];
    pid_t pid;
    char buf;

    if (findPHP(context) == false)
        return true;
    if (pipe(pipefd) == -1)
        return true;
    pid = fork();
    if (pid == -1)
        return true;
    const char *bin = "/usr/bin/php-cgi";
    const char *argv[] = {bin, NULL};    // commande pour lancer l'interpréteur
    char *tmpPath = "tmp/phpExecTmp.XXXXXX";
    int fd;
    
    if ((fd = mkstemp(tmpPath)) == -1)
        return true;
    write(fd, context.getResponse().getBody().c_str(), context.getResponse().getBody().size());
    char *tmpArgv[] = { (char *)"/usr/bin/php-cgi", tmpPath, NULL };
    if (pid == 0) {                             // Le fils
        close(pipefd[0]);
        if (dup2(pipefd[1], 1) == -1)
            exit(84);
        int rc = execve(tmpArgv[0], &tmpArgv[0], nullptr);
        perror("execve");
        _exit(rc);
    } else {
        close(pipefd[1]);
        int exitCode = 0;
        waitpid(pid, &exitCode, 0);
        if (exitCode != 0) {
            std::cout << "PHP Module: execve fail" << std::endl;
            return true;
        }
        unlink(tmpPath);
        close(fd);
        int r = -1;
        char buff[128];
        std::string content;
        while ((r = read(pipefd[0], buff, 128)) != -1 && r > 0)
            content.append(buff, r);
        close(pipefd[0]);
        if (r == -1)
            return true;
        content = content.substr(content.find("<"));
        context.getResponse().getBody() = content;
        context.getResponse().getHeader().set("Content-Length", std::to_string(content.size()));
        return true;
    }
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