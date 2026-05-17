#include <stdio.h>
#include <string.h>
#include "../../include/detect.h"

const char* detect_cpu(void)
{
    static char buf[256];
    FILE* f = fopen("/proc/cpuinfo", "r");
    if (!f) return "Unknown";

    char line[256];
    while (fgets(line, sizeof(line), f))
    {
        if (strncmp(line, "model name", 10) == 0)
        {
            fclose(f);
            char* val = strchr(line, ':');
            if (!val) return "Unknown";
            val += 2; /* skip ": " */
            size_t len = strlen(val);
            while (len > 0 && (val[len-1] == '\n' || val[len-1] == ' '))
                val[--len] = '\0';
            snprintf(buf, sizeof(buf), "%s", val);
            return buf;
        }
    }
    fclose(f);
    return "Unknown";
}
