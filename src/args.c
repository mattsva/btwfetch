#include <string.h>
#include <unistd.h>
#include "args.h"

#include "../include/version.h"

int handle_args(int argc, char** argv)
{
    if (argc <= 1)
        return 0;

    if (strcmp(argv[1], "--help") == 0)
    {
        const char msg[] = "btwfetch --help\nbtwfetch --version\n";
        write(STDOUT_FILENO, msg, sizeof(msg) - 1);
        return 1;
    }

    if (strcmp(argv[1], "--version") == 0)
    {
        write(STDOUT_FILENO, "btwfetch ", 9);
        write(STDOUT_FILENO, BTWFETCH_VERSION, strlen(BTWFETCH_VERSION));
        write(STDOUT_FILENO, "\n", 1);
        return 1;
    }

    return 0;
}
