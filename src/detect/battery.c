#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>

#include "../../include/battery.h"
#include "../../include/common.h"

static void read_field(const char* path, char* buf, size_t size)
{
    if (read_file(path, buf, size) < 0)
    {
        buf[0] = '\0';
        return;
    }
    /* strip trailing newline */
    buf[strcspn(buf, "\n")] = '\0';
}

const char* detect_battery(void)
{
    static char out[128];
    out[0] = '\0';

    const char* base = "/sys/class/power_supply/";
    DIR* dir = opendir(base);
    if (!dir)
        return "N/A";

    struct dirent* e;

    while ((e = readdir(dir)) != NULL)
    {
        if (e->d_name[0] == '.')
            continue;

        char type_path[256];
        snprintf(type_path, sizeof(type_path),
                 "%s%s/type", base, e->d_name);

        char type[32];
        read_field(type_path, type, sizeof(type));

        if (strcmp(type, "Battery") != 0)
            continue;

        /* skip wireless peripherals (mice, keyboards, etc.) */
        if (strstr(e->d_name, "hidpp") != NULL)
            continue;

        char cap_path[256];
        char status_path[256];

        snprintf(cap_path,    sizeof(cap_path),
                 "%s%s/capacity", base, e->d_name);
        snprintf(status_path, sizeof(status_path),
                 "%s%s/status",   base, e->d_name);

        char capacity[16];
        char status[32];

        read_field(cap_path,    capacity, sizeof(capacity));
        read_field(status_path, status,   sizeof(status));

        snprintf(out, sizeof(out), "%s (%s) %s%%",
                 e->d_name, status, capacity);

        closedir(dir);
        return out;
    }

    closedir(dir);
    return "N/A";
}

int detect_batteries(struct battery_info* out, int max)
{
    const char* base = "/sys/class/power_supply/";
    DIR* dir = opendir(base);
    if (!dir)
        return 0;

    struct dirent* e;
    int count = 0;

    while ((e = readdir(dir)) != NULL && count < max)
    {
        if (e->d_name[0] == '.')
            continue;

        char type_path[256];
        snprintf(type_path, sizeof(type_path),
                 "%s%s/type", base, e->d_name);

        char type[32];
        read_field(type_path, type, sizeof(type));

        if (strcmp(type, "Battery") != 0)
            continue;

        struct battery_info* b = &out[count];

        snprintf(b->name, sizeof(b->name), "%s", e->d_name);

        char cap_path[256];
        char status_path[256];

        snprintf(cap_path,    sizeof(cap_path),
                 "%s%s/capacity", base, e->d_name);
        snprintf(status_path, sizeof(status_path),
                 "%s%s/status",   base, e->d_name);

        char cap[16];
        read_field(cap_path,    cap,      sizeof(cap));
        read_field(status_path, b->status, sizeof(b->status));

        b->capacity = atoi(cap);
        count++;
    }

    closedir(dir);
    return count;
}
