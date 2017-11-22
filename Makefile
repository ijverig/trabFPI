OS := $(shell uname)

CC     = cc
DBG    = lldb
CFLAGS = -std=c99 -g -Wall -Wno-deprecated-declarations
ifeq ($(OS), Linux)
	DBG = gdb
endif

build/fotoxope: src/fotoxope.c src/image.c src/transformations.c src/filters.c
	mkdir -p build
	$(CC) $(CFLAGS) -o build/fotoxope src/fotoxope.c src/image.c src/transformations.c src/filters.c

.PHONY: clean run
clean:
	rm -rf build sandbox

run: build/fotoxope
	build/fotoxope test/Underwater_53k.jpg build/output_image.jpg

test: build/fotoxope
	cp -r test/ sandbox/
	ls -1 test/ | sed 's/.jpg*//' | sed 's/.*/build\/fotoxope test\/&.jpg sandbox\/&.output.jpg/' | sh

debug: build/fotoxope
	$(DBG) build/fotoxope test/Underwater_53k.jpg build/output_image.jpg
