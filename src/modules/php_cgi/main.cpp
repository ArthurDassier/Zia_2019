/*
    Petit test pour le CGI PHP pour le Zia
*/

#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <experimental/filesystem>
#include <string>

int main(int argc, char **argv, char **env)
{
    const char *bin = "/usr/bin/php-cgi";

    int rc = execve(
            bin,
            const_cast<char * const *>(argv),
            const_cast<char * const *>(env)
        );
}

/*
    Petit test pour le SSL pour le Zia

    -> info https sur le port 443 et http sur le 80
*/

