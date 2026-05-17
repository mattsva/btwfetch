#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include "../include/layout.h"
#include "../include/ascii.h"

#define MAX_LINES 128

typedef struct {
    const char* left;
    char right[256];
} Line;

static Line lines[MAX_LINES];
static int line_count = 0;

void layout_reset(void)
{
    line_count = 0;
}

void layout_add(const char* left, const char* right)
{
    if (line_count >= MAX_LINES)
        return;

    lines[line_count].left = left ? left : "";

    snprintf(
        lines[line_count].right,
        sizeof(lines[line_count].right),
        "%s",
        right ? right : ""
    );

    line_count++;
}

static void write_str(const char* s)
{
    if (!s)
        return;

    write(STDOUT_FILENO, s, strlen(s));
}

void layout_render(void)
{
    int ascii_lines = ASCII_ART_LINES;
    int max = line_count > ascii_lines ? line_count : ascii_lines;

    for (int i = 0; i < max; i++)
    {
        const char* left = (i < ascii_lines) ? ASCII_ART[i] : "";
        const char* right = (i < line_count) ? lines[i].right : "";

        write_str(left);
        write_str("    ");
        write_str(right);
        write_str("\n");
    }
}
