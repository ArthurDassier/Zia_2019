/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** 
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <iostream>

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

    if (pid == 0) {    // Le fils
        const char *bin = "/usr/bin/php-cgi";
        // const char *argv[] = {bin, NULL};
        close(pipefd[0]);   // Ferme l'extrémité de lecture inutilisée
        if (dup2(pipefd[1], 1) == -1) {
            std::cout << "dup2 a echoue" << std::endl;
            exit(84);
        }

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