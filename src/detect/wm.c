#include <stdlib.h>
#include "../../include/detect.h"

const char* detect_wm(void)
{
    const char* wm = getenv("WAYLAND_DISPLAY");
    if (wm && wm[0]) return "Wayland";
    wm = getenv("DISPLAY");
    if (wm && wm[0]) return "X11";
    return "Unknown";
}
