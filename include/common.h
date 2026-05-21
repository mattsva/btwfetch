#ifndef COMMON_H
#define COMMON_H

#include <stddef.h>
#include <unistd.h>

#define BUFFER_SIZE 4096
#define OUTPUT_SIZE 8192

extern char   output[OUTPUT_SIZE];
extern size_t output_len;

void append(const char* str);
void append_n(const char* str, size_t len);

int read_file(const char* path, char* buffer, size_t size);

/*
 * xwrite: thin wrapper around write() that explicitly discards the return
 * value to suppress -Wunused-result without suppressing real error handling.
 * For output paths where a write failure is not recoverable, this is correct.
 */
static inline void xwrite(int fd, const char* buf, size_t len)
{
    ssize_t r = write(fd, buf, len);
    (void)r;
}

#endif
