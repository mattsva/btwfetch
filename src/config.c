#include <stdio.h>
#include <string.h>

#include "../include/config.h"

static char modules[MAX_CONFIG_MODULES][32];
static int module_count = 0;

int load_config(const char* path)
{
    FILE* f = fopen(path, "r");
    if (!f)
        return -1;

    module_count = 0;

    char line[64];

    while (fgets(line, sizeof(line), f))
    {
        /* strip newline */
        line[strcspn(line, "\n")] = '\0';

        /* skip empty lines and comments */
        if (line[0] == '\0' || line[0] == '#')
            continue;

        if (module_count >= MAX_CONFIG_MODULES)
            break;

        strncpy(modules[module_count], line, 31);
        modules[module_count][31] = '\0';

        module_count++;
    }

    fclose(f);
    return module_count;
}

int get_config_modules(char out[MAX_CONFIG_MODULES][32])
{
    for (int i = 0; i < module_count; i++)
        strcpy(out[i], modules[i]);

    return module_count;
}

int get_config_count(void)
{
    return module_count;
}
