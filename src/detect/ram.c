#include <stdio.h>
#include <string.h>
#include "../../include/detect.h"

const char* detect_ram(void)
{
    static char buf[64];

    FILE* f = fopen("/proc/meminfo", "r");
    if (!f)
        return "Unknown";

    long total = 0, available = 0;
    char line[128];

    while (fgets(line, sizeof(line), f))
    {
        long val;

        if (sscanf(line, "MemTotal: %ld", &val) == 1)
            total = val;
        else if (sscanf(line, "MemAvailable: %ld", &val) == 1)
            available = val;

        /* stop early once we have both values */
        if (total && available)
            break;
    }

    fclose(f);

    if (!total)
        return "Unknown";

    long used = total - available;
    snprintf(buf, sizeof(buf), "%ld MiB / %ld MiB", used / 1024, total / 1024);
    return buf;
}
