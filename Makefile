CC = gcc

CFLAGS = \
	-O3 \
	-flto \
	-march=x86-64-v2 \
	-mtune=generic \
	-pipe \
	-fdata-sections \
	-ffunction-sections \
	-ffile-prefix-map=$(PWD)=. \
	-fno-ident \
	-Wall \
	-Wextra \
	-Wpedantic \
	-Iinclude

LDFLAGS = \
	-flto \
	-Wl,--gc-sections \
	-Wl,-s

SRC = \
	src/main.c \
	src/common.c \
	src/config.c \
	src/module.c \
	src/layout.c \
	src/ascii.c \
	src/args.c \
	src/detect/user.c \
	src/detect/os.c \
	src/detect/kernel.c \
	src/detect/cpu.c \
	src/detect/ram.c \
	src/detect/uptime.c \
	src/detect/shell.c \
	src/detect/de.c \
	src/detect/locale.c \
	src/detect/terminal.c \
	src/detect/wm.c \
	src/detect/theme.c \
	src/detect/icons.c \
	src/detect/resolution.c \
	src/detect/cpu_usage.c \
	src/detect/memory_usage.c \
	src/detect/gpu.c \
	src/detect/packages.c \
	src/detect/disk.c \
	src/detect/battery.c \
	src/detect/network.c

OBJ = $(SRC:.c=.o)

TARGET = btwfetch

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(OBJ) $(TARGET)

run: all
	./$(TARGET)
