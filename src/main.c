#include <unistd.h>
#include <string.h>

#include "../include/common.h"
#include "../include/config.h"
#include "../include/version.h"

static void print_help(void)
{
 const char msg[] =
  "btwfetch - system information tool\n\n"
  "Usage:\n"
  "  btwfetch               Run system fetch\n"
  "  btwfetch --help        Show help\n"
  "  btwfetch --version     Show version\n";

 write(STDOUT_FILENO, msg, sizeof(msg) - 1);
}

static void print_version(void)
{
 const char prefix[] = "btwfetch version ";
 const char suffix[] = "\n";

 write(STDOUT_FILENO, prefix, sizeof(prefix) - 1);
 write(STDOUT_FILENO, BTWFETCH_VERSION, strlen(BTWFETCH_VERSION));
 write(STDOUT_FILENO, suffix, sizeof(suffix) - 1);
}

static int handle_args(int argc, char** argv)
{
 if (argc <= 1)
  return 0;

 if (strcmp(argv[1], "--help") == 0)
 {
  print_help();
  return 1;
 }
 if (strcmp(argv[1], "--version") == 0)
 {
  print_version();
  return 1;
 }

 return 0;
}

int main(int argc, char** argv)
{
 if (handle_args(argc, argv))
  return 0;

 load_config("config/default.conf");

 write(STDOUT_FILENO, output, output_len);

 return 0;
}
