#include <stdio.h>
#include "../../include/detect.h"

const char* detect_uptime(void)
{
    static char buf[64];

    FILE* f = fopen("/proc/uptime", "r");
    if (!f)
        return "Unknown";

    double secs = 0;
    int parsed = fscanf(f, "%lf", &secs);
    fclose(f);

    if (parsed != 1)
        return "Unknown";

    int d = (int)(secs / 86400);
    int h = (int)((secs - d * 86400) / 3600);
    int m = (int)((secs - d * 86400 - h * 3600) / 60);

    if (d > 0)
        snprintf(buf, sizeof(buf), "%dd %dh %dm", d, h, m);
    else if (h > 0)
        snprintf(buf, sizeof(buf), "%dh %dm", h, m);
    else
        snprintf(buf, sizeof(buf), "%dm", m);

    return buf;
}
