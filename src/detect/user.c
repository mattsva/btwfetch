#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>

#include "../../include/detect.h"

const char* detect_user(void)
{
    static char buf[128];
    struct passwd* pw = getpwuid(getuid());
    if (pw)
    {
        char hostname[64] = {0};
        gethostname(hostname, sizeof(hostname) - 1);
        snprintf(buf, sizeof(buf), "%s@%s", pw->pw_name, hostname);
        return buf;
    }
    return "unknown";
}
