#include <stdio.h>
#include <string.h>
#include "../../include/detect.h"

const char* detect_ram(void)
{
    static char buf[64];
    FILE* f = fopen("/proc/meminfo", "r");
    if (!f) return "Unknown";

    long total = 0, available = 0;
    char key[64];
    long val;
    char unit[16];

    while (fscanf(f, "%63s %ld %15s\n", key, &val, unit) == 3)
    {
        if (strcmp(key, "MemTotal:") == 0) total = val;
        if (strcmp(key, "MemAvailable:") == 0) available = val;
    }
    fclose(f);

    long used = total - available;
    snprintf(buf, sizeof(buf), "%ld MiB / %ld MiB", used / 1024, total / 1024);
    return buf;
}
