#ifndef BATTERY_H
#define BATTERY_H

#include <stddef.h>

/* future structured battery info */
struct battery_info {
    char name[64];
    char status[32];
    int  capacity;
};

/* detect_battery is declared in detect.h — use that header for the primary API */
int detect_batteries(struct battery_info* out, int max);

#endif
