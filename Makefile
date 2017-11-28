OS := $(shell uname)

CC     = cc
DBG    = lldb
CFLAGS = -std=c99 -g -Wall -Wno-deprecated-declarations
ifeq ($(OS), Linux)
	DBG = gdb
endif

build/fotoxope: src/fotoxope.c src/image.c src/transformations.c src/filters.c src/cli_options.c
	mkdir -p build
	$(CC) $(CFLAGS) -o build/fotoxope src/fotoxope.c src/image.c src/transformations.c src/filters.c src/cli_options.c

.PHONY: clean test
clean:
	rm -rf build sandbox

test: fliph flipv gray quantize

fliph: build/fotoxope
	cp -r test/ sandbox/
	ls -1 test/ | sed 's/.jpg*//' | sed 's/.*/build\/fotoxope -F h test\/&.jpg sandbox\/&.output.fliph.jpg/' | sh

flipv: build/fotoxope
	cp -r test/ sandbox/
	ls -1 test/ | sed 's/.jpg*//' | sed 's/.*/build\/fotoxope -F v test\/&.jpg sandbox\/&.output.flipv.jpg/' | sh

gray: build/fotoxope
	cp -r test/ sandbox/
	ls -1 test/ | sed 's/.jpg*//' | sed 's/.*/build\/fotoxope -G test\/&.jpg sandbox\/&.output.gray.jpg/' | sh

quantize: build/fotoxope
	cp -r test/ sandbox/
	ls -1 test/ | sed 's/.jpg*//' | sed 's/.*/build\/fotoxope -Q 6 test\/&.jpg sandbox\/&.output.quantize.jpg/' | sh

debug: build/fotoxope
	$(DBG) build/fotoxope test/Underwater_53k.jpg build/output_image.jpg
