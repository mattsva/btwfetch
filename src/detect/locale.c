#include <stdlib.h>
#include "../../include/detect.h"

const char* detect_locale(void)
{
    const char* loc = getenv("LANG");
    if (loc && loc[0]) return loc;
    loc = getenv("LC_ALL");
    if (loc && loc[0]) return loc;
    return "Unknown";
}
