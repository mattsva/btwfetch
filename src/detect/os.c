#include <string.h>

#include "../../include/common.h"

void detect_os(void)
{
 char buffer[BUFFER_SIZE];

 if(read_file("/etc/os-release", buffer, sizeof(buffer)) < 0)
  return;

 char* pretty = strstr(buffer, "PRETTY_NAME=");
 if(!pretty)
  return;

 pretty += 12;

 if(*pretty == '"')
  pretty++;

 char* end = strchr(pretty, '\n');

 if(end)
  *end = '\0';

 size_t len = strlen(pretty);

 if(len > 0 && pretty[len - 1] == '"')
  pretty[len - 1] = '\0';

 append("OS: ");
 append(pretty);
 append("\n");
}
