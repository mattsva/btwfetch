#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>

#include "../../include/detect.h"

#define CACHE_FILE "/tmp/btwfetch_pkg_cache"

typedef struct {
    int flatpak;
    int nix_system;
    int nix_user;
    int pacman;
    int dpkg;
    int apk;
    int rpm;
    int xbps;
} PackageCount;

static int dir_count(const char* path)
{
    DIR* dir = opendir(path);
    if (!dir)
        return 0;

    struct dirent* e;
    int count = 0;

    while ((e = readdir(dir)))
    {
        if (e->d_name[0] != '.')
            count++;
    }

    closedir(dir);
    return count;
}

static int file_count_prefix(const char* path, const char* prefix)
{
    FILE* f = fopen(path, "r");
    if (!f)
        return 0;

    char line[512];
    size_t len = strlen(prefix);
    int count = 0;

    while (fgets(line, sizeof(line), f))
    {
        if (strncmp(line, prefix, len) == 0)
            count++;
    }

    fclose(f);
    return count;
}

/* cache (simple /tmp) */
static int load_cache(char* out, size_t sz)
{
    FILE* f = fopen(CACHE_FILE, "r");
    if (!f)
        return 0;

    if (!fgets(out, sz, f))
    {
        fclose(f);
        return 0;
    }

    fclose(f);
    return 1;
}

static void write_cache(const char* str)
{
    FILE* f = fopen(CACHE_FILE, "w");
    if (!f)
        return;

    fputs(str, f);
    fclose(f);
}

static void detect_all(PackageCount* p)
{
    memset(p, 0, sizeof(*p));

    /* Flatpak (global) */
    p->flatpak = dir_count("/var/lib/flatpak/app");

    /* NixOS system packages */
    p->nix_system =
        dir_count("/run/current-system/sw/bin");

    /* NixOS user packages */
    p->nix_user =
        dir_count("/nix/var/nix/profiles/per-user") +
        dir_count("/home");

    /* Pacman (Arch) */
    p->pacman = dir_count("/var/lib/pacman/local");

    /* dpkg (Debian/Ubuntu) */
    p->dpkg = file_count_prefix("/var/lib/dpkg/status", "Package:");

    /* apk (Alpine) */
    p->apk = file_count_prefix("/lib/apk/db/installed", "P:");

    /* rpm (Fedora/RHEL/SUSE fallback) */
    p->rpm = dir_count("/var/lib/rpm");

    /* xbps (Void) */
    p->xbps = dir_count("/var/db/xbps/pkgdb");
}

const char* detect_packages(void)
{
    static char buf[256];
    static PackageCount p;

    /* try cache */
    if (load_cache(buf, sizeof(buf)))
        return buf;

    detect_all(&p);

    /* build output */
    if (p.pacman > 0)
    {
        snprintf(buf, sizeof(buf),
            "%d (pacman)", p.pacman);
    }
    else if (p.dpkg > 0)
    {
        snprintf(buf, sizeof(buf),
            "%d (dpkg)", p.dpkg);
    }
    else if (p.apk > 0)
    {
        snprintf(buf, sizeof(buf),
            "%d (apk)", p.apk);
    }
    else if (p.rpm > 0)
    {
        snprintf(buf, sizeof(buf),
            "%d (rpm)", p.rpm);
    }
    else if (p.xbps > 0)
    {
        snprintf(buf, sizeof(buf),
            "%d (xbps)", p.xbps);
    }
    else
    {
        /* NixOS multi-value output */
        snprintf(buf, sizeof(buf),
            "%d (flatpak), %d (nix-system), %d (nix-user)", // TODO: This does not work correctly, its not as many packages as the system really has
            p.flatpak,
            p.nix_system,
            p.nix_user);
    }

    write_cache(buf);
    return buf;
}
