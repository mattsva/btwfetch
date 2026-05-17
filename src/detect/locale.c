#include <stdlib.h>

#include "../../include/common.h"

void detect_locale(void)
{
 const char* locale = getenv("LANG");

 if(!locale)
  return;

 append("Locale: ");
 append(locale);
 append("\n");
}
