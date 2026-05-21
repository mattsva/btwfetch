#include <stdio.h>
#include <string.h>

#include "../../include/detect.h"

const char* detect_os(void)
{
    static char buf[256];
    char line[256];

    FILE* f = fopen("/etc/os-release", "r");
    if (!f)
        return "Unknown";

    while (fgets(line, sizeof(line), f))
    {
        if (strncmp(line, "PRETTY_NAME=", 12) != 0)
            continue;

        fclose(f);

        char* val = line + 12;

        /* strip surrounding quotes and trailing newline */
        if (val[0] == '"')
            val++;

        size_t len = strlen(val);
        while (len > 0 && (val[len - 1] == '\n' || val[len - 1] == '"'))
            val[--len] = '\0';

        snprintf(buf, sizeof(buf), "%s", val);
        return buf;
    }

    fclose(f);
    return "Unknown";
}
