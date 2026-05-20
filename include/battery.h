#ifndef BATTERY_H
#define BATTERY_H

#include <stddef.h>

const char* detect_battery(void);

/* future extensions */
struct battery_info {
    char name[64];
    char status[32];
    int capacity;
};

/* for later structured access */
int detect_batteries(struct battery_info *out, int max);

#endif
