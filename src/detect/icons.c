#include <stdlib.h>

#include "../../include/common.h"

void detect_icons(void)
{
 const char* icons = getenv("ICON_THEME");

 if(!icons)
  return;

 append("Icons: ");
 append(icons);
 append("\n");
}
