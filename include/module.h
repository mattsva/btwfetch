#ifndef MODULE_H
#define MODULE_H

typedef struct
{
 const char* name;
 void (*function)(void);
} Module;

extern Module modules[];

#endif
