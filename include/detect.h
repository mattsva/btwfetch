#ifndef DETECT_H
#define DETECT_H

void detect_user(void);
void detect_os(void);
void detect_kernel(void);
void detect_cpu(void);
void detect_ram(void);
void detect_uptime(void);
void detect_shell(void);
void detect_de(void);
void detect_locale(void);

void detect_terminal(void);
void detect_wm(void);
void detect_theme(void);
void detect_icons(void);
void detect_resolution(void);

void detect_cpu_usage(void);
void detect_memory_usage(void);

void detect_gpu(void);
void detect_packages(void);
void detect_disk(void);
void detect_battery(void);
void detect_network(void);

#endif
