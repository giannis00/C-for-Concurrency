# Builds every example and solution into the folder "build".
#   make         build everything
#   make clean   remove the folder "build"

CC     = gcc
CFLAGS = -std=c11 -Wall -Wextra -g

SOURCES  := $(wildcard */examples/*.c */solutions/*.c)
PROGRAMS := $(patsubst %.c,build/%,$(SOURCES))

all: $(PROGRAMS)

build/%: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -o $@ -lm

clean:
	rm -rf build

.PHONY: all clean
