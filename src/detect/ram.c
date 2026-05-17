#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../../include/common.h"

void detect_ram(void)
{
 char buffer[BUFFER_SIZE];

 if(read_file("/proc/meminfo", buffer, sizeof(buffer)) < 0)
  return;

 char* mem = strstr(buffer, "MemTotal:");

 if(!mem)
  return;

 mem += 9;

 while(*mem == ' ')
  mem++;

 long kb = atol(mem);

 long mb = kb / 1024;

 char temp[64];

 snprintf(temp, sizeof(temp), "%ld MB\n", mb);

 append("RAM: ");
 append(temp);
}
