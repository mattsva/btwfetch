#include <string.h>
#include <stdio.h>

#include "../include/module.h"
#include "../include/layout.h"
#include "../include/detect.h"

#define MAX_MODULES 64

static Module modules[MAX_MODULES];
static int module_count = 0;

static void add_module(const char* name, const char* (*fn)(void))
{
    if (module_count >= MAX_MODULES)
        return;

    modules[module_count].name = name;
    modules[module_count].run  = fn;

    module_count++;
}

void register_modules(void)
{
    add_module("user",         detect_user);
    add_module("os",           detect_os);
    add_module("kernel",       detect_kernel);
    add_module("uptime",       detect_uptime);
    add_module("shell",        detect_shell);
    add_module("terminal",     detect_terminal);
    add_module("de",           detect_de);
    add_module("wm",           detect_wm);
    add_module("theme",        detect_theme);
    add_module("icons",        detect_icons);
    add_module("resolution",   detect_resolution);
    add_module("cpu",          detect_cpu);
    add_module("cpu_usage",    detect_cpu_usage);
    add_module("ram",          detect_ram);
    add_module("memory_usage", detect_memory_usage);
    add_module("gpu",          detect_gpu);
    add_module("packages",     detect_packages);
    add_module("disk",         detect_disk);
    add_module("battery",      detect_battery);
    add_module("network",      detect_network);
    add_module("locale",       detect_locale);
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
