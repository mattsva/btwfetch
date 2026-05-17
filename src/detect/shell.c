
#include <stdlib.h>
#include <string.h>

#include "../../include/common.h"

void detect_shell(void)
{
 const char* shell = getenv("SHELL");

 if(!shell)
  return;

 const char* name = strrchr(shell, '/');

 if(name)
  shell = name + 1;

 append("Shell: ");
 append(shell);
 append("\n");
}
