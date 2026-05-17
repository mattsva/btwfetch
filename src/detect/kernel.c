#include <sys/utsname.h>

#include "../../include/common.h"

void detect_kernel(void)
{
 struct utsname uts;
 if(uname(&uts) != 0)
  return;
 append("Kernel: ");
 append(uts.release);
 append("\n");
}
