#include <string.h>

#include "../../include/common.h"

void detect_cpu(void)
{
 char buffer[BUFFER_SIZE];

 if(read_file("/proc/cpuinfo", buffer, sizeof(buffer)) < 0)
  return;

 char* model = strstr(buffer, "model name");

 if(!model)
  return;

 model = strchr(model, ':');
 if(!model)
  return;

 model += 2;

 char* end = strchr(model, '\n');

 if(!end)
  return;

 append("CPU: ");
 append_n(model, (size_t)(end - model));
 append("\n");
}
