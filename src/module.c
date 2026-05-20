#include <string.h>
#include <stdio.h>

#include "../include/module.h"
#include "../include/layout.h"
#include "../include/detect.h"

static Module modules[32];
static int module_count = 0;

static void add_module(const char* name, const char* (*fn)(void))
{
    modules[module_count++] = (Module){ name, fn };
}

void register_modules(void)
{
    add_module("user", detect_user);
    add_module("os", detect_os);
    add_module("kernel", detect_kernel);
    add_module("uptime", detect_uptime);
    add_module("shell", detect_shell);
    add_module("de", detect_de);
    add_module("locale", detect_locale);
    add_module("terminal", detect_terminal);
    add_module("wm", detect_wm);
    add_module("battery", detect_battery);
}

const char* run_module(const char* name)
{
    for (int i = 0; i < module_count; i++)
    {
        if (strcmp(modules[i].name, name) == 0)
            return modules[i].run();
    }
    return "";
}
