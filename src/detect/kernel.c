#include <stdio.h>
#include <string.h>
#include <sys/utsname.h>

#include "../../include/detect.h"

const char* detect_kernel(void)
{
    static char buf[256];
    struct utsname u;

    if (uname(&u) == 0)
    {
        snprintf(buf, sizeof(buf), "%s", u.release);
        return buf;
    }

    return "Unknown";
}
