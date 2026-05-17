#include <stdlib.h>
#include "../../include/detect.h"

const char* detect_terminal(void)
{
    const char* t = getenv("TERM_PROGRAM");
    if (t && t[0]) return t;
    t = getenv("TERM");
    if (t && t[0]) return t;
    return "Unknown";
}
