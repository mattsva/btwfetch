#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include "../include/common.h"

char output[OUTPUT_SIZE];
size_t output_len = 0;

void append(const char* str)
{
 while(*str && output_len < OUTPUT_SIZE - 1)
 {
  output[output_len++] = *str++;
 }
}

void append_n(const char* str, size_t len)
{
 if(output_len + len >= OUTPUT_SIZE)
  len = OUTPUT_SIZE - output_len - 1;

 memcpy(output + output_len, str, len);

 output_len += len;
}

int read_file(const char* path, char* buffer, size_t size)
{
 int fd = open(path, O_RDONLY);

 if(fd < 0)
  return -1;

 ssize_t bytes = read(fd, buffer, size - 1);

 close(fd);

 if(bytes <= 0)
  return -1;

 buffer[bytes] = '\0';

 return (int)bytes;
}
