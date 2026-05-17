#include <stdio.h>

#include "../../include/common.h"

void detect_uptime(void)
{
 char buffer[BUFFER_SIZE];

 if(read_file("/proc/uptime", buffer, sizeof(buffer)) < 0)
  return;

 double uptime_seconds = 0.0;

 sscanf(buffer, "%lf", &uptime_seconds);
 long seconds = (long) uptime_seconds;
 long hours = seconds / 3600;
 long minutes = (seconds % 3600) / 60;

 char temp[128];

 snprintf(
  temp,
  sizeof(temp),
  "%ldh %ldm\n",
  hours,
  minutes
 );

 append("Uptime: ");
 append(temp);
}
