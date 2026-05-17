#ifndef CONFIG_H
#define CONFIG_H

#define MAX_CONFIG_MODULES 64

int load_config(const char* path);
int get_config_modules(char modules[MAX_CONFIG_MODULES][32]);

int get_config_count(void);

#endif
