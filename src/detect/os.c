#include <stdio.h>
#include <string.h>

#include "../../include/detect.h"

const OSInfo* detect_os_raw(void)
{
    static OSInfo info;
    static int initialized = 0;

    if (initialized)
        return &info;

    info.pretty_name[0] = '\0';
    info.id[0] = '\0';
    info.id_like[0] = '\0';

    FILE* f = fopen("/etc/os-release", "r");
    if (!f)
    {
        strcpy(info.pretty_name, "Unknown");
        strcpy(info.id, "unknown");
        initialized = 1;
        return &info;
    }

    char line[256];

    while (fgets(line, sizeof(line), f))
    {
        char* val;

        /* PRETTY_NAME */
        if (strncmp(line, "PRETTY_NAME=", 12) == 0)
        {
            val = line + 12;

            if (*val == '"')
                val++;

            size_t len = strlen(val);
            while (len && (val[len - 1] == '\n' || val[len - 1] == '"'))
                val[--len] = '\0';

            strncpy(info.pretty_name, val, sizeof(info.pretty_name) - 1);
            info.pretty_name[sizeof(info.pretty_name) - 1] = '\0';
        }

        /* ID */
        else if (strncmp(line, "ID=", 3) == 0)
        {
            val = line + 3;

            if (*val == '"')
                val++;

            size_t len = strlen(val);
            while (len && (val[len - 1] == '\n' || val[len - 1] == '"'))
                val[--len] = '\0';

            strncpy(info.id, val, sizeof(info.id) - 1);
            info.id[sizeof(info.id) - 1] = '\0';
        }

        /* ID_LIKE */
        else if (strncmp(line, "ID_LIKE=", 8) == 0)
        {
            val = line + 8;

            if (*val == '"')
                val++;

            size_t len = strlen(val);
            while (len && (val[len - 1] == '\n' || val[len - 1] == '"'))
                val[--len] = '\0';

            strncpy(info.id_like, val, sizeof(info.id_like) - 1);
            info.id_like[sizeof(info.id_like) - 1] = '\0';
        }
    }

    fclose(f);

    if (!info.pretty_name[0])
        strcpy(info.pretty_name, "Unknown");

    if (!info.id[0])
        strcpy(info.id, "unknown");

    initialized = 1;
    return &info;
}

const char* detect_os(void)
{
    static char buf[256];

    const OSInfo* os = detect_os_raw();

    snprintf(buf, sizeof(buf),
             "%s",
             os->pretty_name);

    return buf;
}
