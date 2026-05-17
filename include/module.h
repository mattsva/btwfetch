#ifndef MODULE_H
#define MODULE_H

typedef struct {
    const char* name;
    const char* (*run)(void);
} Module;

void register_modules(void);
const char* run_module(const char* name);

#endif
