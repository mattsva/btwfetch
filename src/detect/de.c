#include <stdlib.h>

#include "../../include/common.h"

void detect_de(void)
{
 const char* de = getenv("XDG_CURRENT_DESKTOP");

 if(!de)
  de = getenv("DESKTOP_SESSION");

 if(!de)
  return;

 append("DE: ");
 append(de);
 append("\n");
}
