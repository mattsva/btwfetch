#include <stdlib.h>
#include <string.h>
#include "../../include/detect.h"

const char* detect_shell(void)
{
    const char* shell = getenv("SHELL");
    if (!shell)
        return "Unknown";

    /* return basename */
    const char* base = strrchr(shell, '/');
    return base ? base + 1 : shell;
}
