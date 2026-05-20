#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <sys/types.h>

#include "../include/args.h"
#include "../include/module.h"
#include "../include/layout.h"
#include "../include/config.h"
#include "../include/version.h"

static void add_line(const char* key)
{
    const char* value = run_module(key);

    if (!value || value[0] == '\0')
        value = "N/A";

    char buffer[512];

    snprintf(buffer,
             sizeof(buffer),
             "%s: %s",
             key,
             value);

    layout_add("", buffer);
}

int main(int argc, char** argv)
{
    if (handle_args(argc, argv))
        return 0;

    register_modules();

    struct passwd* pw = getpwuid(getuid());

    if (!pw)
    {
        write(STDERR_FILENO,
              "failed to get home directory\n",
              30);

        return 1;
    }

    const char* home = pw->pw_dir;

    char config_path[512];

    snprintf(config_path,
             sizeof(config_path),
             "%s/.config/btwfetch/default.conf",
             home);

    if (load_config(config_path) < 0)
    {
        perror("load_config");
        return 1;
    }

    char modules[MAX_CONFIG_MODULES][32];

    get_config_modules(modules);

    int count = get_config_count();

    for (int i = 0; i < count; ++i)
    {
        add_line(modules[i]);
    }

    layout_render();

    return 0;
}
