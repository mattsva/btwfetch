#include <stdlib.h>
#include "../../include/detect.h"

const char* detect_de(void)
{
    const char* de = getenv("XDG_CURRENT_DESKTOP");
    if (de && de[0]) return de;
    de = getenv("DESKTOP_SESSION");
    if (de && de[0]) return de;
    return "Unknown";
}
