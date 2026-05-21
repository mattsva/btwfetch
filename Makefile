kkkkCC ?= cc
PREFIX ?= /usr/local

CFLAGS = \
	-O2 \
	-mtune=generic \
	-fdata-sections \
	-ffunction-sections \
	-ffile-prefix-map=$(PWD)=. \
	-fno-ident \
	-Wall \
	-Wextra \
	-Wpedantic \
	-Iinclude

LDFLAGS = \
	-Wl,--gc-sections

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

.PHONY: all clean run install

all: $(TARGET)

# ✔ explicit compile rule (important for Nix + reproducibility)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(OBJ) $(TARGET)

run: all
	./$(TARGET)

install: all
	install -Dm755 $(TARGET) $(DESTDIR)$(PREFIX)/bin/$(TARGET)

	install -Dm644 \
		config/config.conf \
		$(DESTDIR)$(PREFIX)/share/btwfetch/config.conf
