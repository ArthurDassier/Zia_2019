/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** 
*/

#include <unistd.h>

int main(int argc, char **argv, char **env)
{
    const char *bin = "/usr/bin/php-cgi";

    int rc = execve(
            bin,
            const_cast<char * const *>(argv),
            const_cast<char * const *>(env)
        );
}