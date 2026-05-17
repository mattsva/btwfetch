#include <sys/utsname.h>
#include "../../include/detect.h"

const char* detect_kernel(void)
{
    static char buf[256];
    static struct utsname u;
    if (uname(&u) == 0)
    {
        __builtin_strncpy(buf, u.release, sizeof(buf) - 1);
        buf[sizeof(buf) - 1] = '\0';
        return buf;
    }
    return "Unknown";
}
