#include <string.h>
#include <stdio.h>

#include "../include/args.h"
#include "../include/common.h"
#include "../include/version.h"

int handle_args(int argc, char** argv)
{
    if (argc <= 1)
        return 0;

    if (strcmp(argv[1], "--help") == 0)
    {
        const char msg[] =
            "Usage: btwfetch [OPTION]\n"
            "\n"
            "  --help       Show this help message\n"
            "  --version    Print version and exit\n";
        xwrite(STDOUT_FILENO, msg, sizeof(msg) - 1);
        return 1;
    }

    if (strcmp(argv[1], "--version") == 0)
    {
        xwrite(STDOUT_FILENO, "btwfetch ", 9);
        xwrite(STDOUT_FILENO, BTWFETCH_VERSION, strlen(BTWFETCH_VERSION));
        xwrite(STDOUT_FILENO, "\n", 1);
        return 1;
    }

    /* unknown argument */
    fprintf(stderr, "error: unknown option '%s'\n", argv[1]);
    fprintf(stderr, "Try 'btwfetch --help' for usage.\n");
    return -1;
}
