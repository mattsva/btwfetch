#include <stdlib.h>
#include "../../include/detect.h"

/*
 * detect_wm: reports the active display server / compositor protocol.
 * True WM detection (via _NET_WM_NAME or wmctrl) requires X11/Wayland
 * libraries and is left as a future improvement.
 */
const char* detect_wm(void)
{
    if (getenv("WAYLAND_DISPLAY"))
        return "Wayland";

    if (getenv("DISPLAY"))
        return "X11";

    return "Unknown";
}
