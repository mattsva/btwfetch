#include <unistd.h>
#include <pwd.h>

#include "../../include/common.h"

void detect_user(void)
{
 char hostname[256];

 if(gethostname(hostname, sizeof(hostname)) != 0)
  return;

 struct passwd* pw = getpwuid(getuid());

 if(!pw)
  return;

 append(pw->pw_name);
 append("@");
 append(hostname);
 append("\n");
}
