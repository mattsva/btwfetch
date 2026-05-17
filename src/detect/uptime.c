#include <stdio.h>
#include "../../include/detect.h"

const char* detect_uptime(void)
{
    static char buf[64];

    FILE* f = fopen("/proc/uptime", "r");
    if (!f)
        return "Unknown";

    double secs = 0;
    fscanf(f, "%lf", &secs);
    fclose(f);

    int h = (int)(secs / 3600);
    int m = (int)((secs - h * 3600) / 60);

    if (h > 0)
        snprintf(buf, sizeof(buf), "%dh %dm", h, m);
    else
        snprintf(buf, sizeof(buf), "%dm", m);

    return buf;
}
