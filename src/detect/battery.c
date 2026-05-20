#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>

#include "battery.h"

static void read_file(const char *path, char *buf, size_t size)
{
    int fd = open(path, O_RDONLY);
    if (fd < 0) {
        buf[0] = '\0';
        return;
    }

    ssize_t n = read(fd, buf, size - 1);
    close(fd);

    if (n <= 0) {
        buf[0] = '\0';
        return;
    }

    buf[n] = '\0';
    buf[strcspn(buf, "\n")] = '\0';
}

const char* detect_battery(void)
{
    static char out[128];
    out[0] = '\0';

    const char *base = "/sys/class/power_supply/";
    DIR *dir = opendir(base);
    if (!dir)
        return "N/A";

    struct dirent *e;

    while ((e = readdir(dir)) != NULL) {

        if (e->d_name[0] == '.')
            continue;

        char type_path[256];
        snprintf(type_path, sizeof(type_path),
                 "%s%s/type", base, e->d_name);

        char type[32];
        read_file(type_path, type, sizeof(type));

        if (strcmp(type, "Battery") != 0)
            continue;

        if (strstr(e->d_name, "hidpp") != NULL)
            continue;

        char cap_path[256];
        char status_path[256];

        snprintf(cap_path, sizeof(cap_path),
                 "%s%s/capacity", base, e->d_name);

        snprintf(status_path, sizeof(status_path),
                 "%s%s/status", base, e->d_name);

        char capacity[16];
        char status[32];

        read_file(cap_path, capacity, sizeof(capacity));
        read_file(status_path, status, sizeof(status));

        snprintf(out, sizeof(out),
                 "%s (%s) %s%%",
                 e->d_name,
                 status,
                 capacity);

        closedir(dir);
        return out;   /* ONLY FIRST VALID BATTERY */
    }

    closedir(dir);
    return "N/A";
}

/* optional structured API (future use) not yet */
int detect_batteries(struct battery_info *out, int max)
{
    const char *base = "/sys/class/power_supply/";
    DIR *dir = opendir(base);
    if (!dir)
        return 0;

    struct dirent *e;
    int count = 0;

    while ((e = readdir(dir)) != NULL && count < max) {

        if (e->d_name[0] == '.')
            continue;

        char type_path[256];
        snprintf(type_path, sizeof(type_path),
                 "%s%s/type", base, e->d_name);

        char type[32];
        read_file(type_path, type, sizeof(type));

        if (strcmp(type, "Battery") != 0)
            continue;

        struct battery_info *b = &out[count];

        snprintf(b->name, sizeof(b->name), "%s", e->d_name);

        char cap_path[256];
        char status_path[256];

        snprintf(cap_path, sizeof(cap_path),
                 "%s%s/capacity", base, e->d_name);

        snprintf(status_path, sizeof(status_path),
                 "%s%s/status", base, e->d_name);

        char cap[16];

        read_file(cap_path, cap, sizeof(cap));
        read_file(status_path, b->status, sizeof(b->status));

        b->capacity = atoi(cap);

        count++;
    }

    closedir(dir);
    return count;
}
