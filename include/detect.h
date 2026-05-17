#ifndef DETECT_H
#define DETECT_H

const char* detect_user(void);
const char* detect_os(void);
const char* detect_kernel(void);
const char* detect_cpu(void);
const char* detect_ram(void);
const char* detect_uptime(void);
const char* detect_shell(void);
const char* detect_de(void);
const char* detect_locale(void);
const char* detect_terminal(void);
const char* detect_wm(void);
const char* detect_theme(void);
const char* detect_icons(void);
const char* detect_resolution(void);
const char* detect_cpu_usage(void);
const char* detect_memory_usage(void);
const char* detect_gpu(void);
const char* detect_packages(void);
const char* detect_disk(void);
const char* detect_battery(void);
const char* detect_network(void);

#endif
