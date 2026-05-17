#include <stdlib.h>

#include "../../include/common.h"

void detect_theme(void)
{
 const char* theme = getenv("GTK_THEME");

 if(!theme)
  return;

 append("Theme: ");
 append(theme);
 append("\n");
}
