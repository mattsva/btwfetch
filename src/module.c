#include <string.h>

#include "../include/module.h"
#include "../include/detect.h"

Module modules[] =
{
 {"user", detect_user},
 {"os", detect_os},
 {"kernel", detect_kernel},
 {"uptime", detect_uptime},
 {"shell", detect_shell},
 {"terminal", detect_terminal},
 {"de", detect_de},
 {"wm", detect_wm},
 {"theme", detect_theme},
 {"icons", detect_icons},
 {"resolution", detect_resolution},
 {"cpu", detect_cpu},
 {"cpu_usage", detect_cpu_usage},
 {"ram", detect_ram},
 {"memory_usage", detect_memory_usage},
 {"gpu", detect_gpu},
 {"packages", detect_packages},
 {"disk", detect_disk},
 {"battery", detect_battery},
 {"network", detect_network},
 {"locale", detect_locale},
 {NULL, NULL}
};
