#include <unistd.h>
#include <string.h>
#include <stdio.h>

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
    snprintf(buffer, sizeof(buffer), "%s: %s", key, value);

    layout_add("", buffer);
}

int main(int argc, char** argv)
{
    if (handle_args(argc, argv))
        return 0;

    register_modules();

    if (load_config("config/default.conf") < 0)
    {
        write(STDERR_FILENO, "failed to load config\n", 22);
        return 1;
    }

    char modules[64][32];
    int count = get_config_modules(modules);

    layout_reset();

    for (int i = 0; i < count; i++)
    {
        add_line(modules[i]);
    }

    layout_render();

    return 0;
}
