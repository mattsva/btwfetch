#include <stdlib.h>

#include "../../include/common.h"

void detect_wm(void)
{
 const char* wm = getenv("XDG_SESSION_DESKTOP");

 if(!wm)
  return;

 append("WM: ");
 append(wm);
 append("\n");
}
