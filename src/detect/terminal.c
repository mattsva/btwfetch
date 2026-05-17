
#include <stdlib.h>

#include "../../include/common.h"

void detect_terminal(void)
{
 const char* term = getenv("TERM");

 if(!term)
  return;

 append("Terminal: ");
 append(term);
 append("\n");
}
