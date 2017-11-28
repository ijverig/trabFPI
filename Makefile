OS := $(shell uname)

CC     = cc
DBG    = lldb
CFLAGS = -std=c99 -g -Wall -Wno-deprecated-declarations
ifeq ($(OS), Linux)
	DBG = gdb
endif

build/fotoxope: src/fotoxope.c src/image.[hc] src/transformations.[hc] src/filters.[hc] src/cli_options.[hc] src/version.h
	mkdir -p build
	$(CC) $(CFLAGS) -o build/fotoxope src/fotoxope.c src/image.c src/transformations.c src/filters.c src/cli_options.c

.PHONY: clean test
clean:
	rm -rf build sandbox

test: version fliph flipv gray quantize

version: build/fotoxope
	build\/fotoxope -v src/version.h && \
	build\/fotoxope --version src/version.h

fliph: build/fotoxope sandbox
	ls -1 test/ | sed 's/.jpg*//' | sed 's/.*/build\/fotoxope -F h test\/&.jpg sandbox\/&.output.fliph.jpg/' | sh && \
	ls -1 test/ | sed 's/.jpg*//' | sed 's/.*/build\/fotoxope --flip horizontal test\/&.jpg sandbox\/&.output.fliph.jpg/' | sh

flipv: build/fotoxope sandbox
	ls -1 test/ | sed 's/.jpg*//' | sed 's/.*/build\/fotoxope -F v test\/&.jpg sandbox\/&.output.flipv.jpg/' | sh && \
	ls -1 test/ | sed 's/.jpg*//' | sed 's/.*/build\/fotoxope --flip vertical test\/&.jpg sandbox\/&.output.flipv.jpg/' | sh

gray: build/fotoxope sandbox
	ls -1 test/ | sed 's/.jpg*//' | sed 's/.*/build\/fotoxope -G test\/&.jpg sandbox\/&.output.gray.jpg/' | sh && \
	ls -1 test/ | sed 's/.jpg*//' | sed 's/.*/build\/fotoxope --gray test\/&.jpg sandbox\/&.output.gray.jpg/' | sh

quantize: build/fotoxope sandbox
	ls -1 test/ | sed 's/.jpg*//' | sed 's/.*/build\/fotoxope -Q 6 test\/&.jpg sandbox\/&.output.quantize.jpg/' | sh && \
	ls -1 test/ | sed 's/.jpg*//' | sed 's/.*/build\/fotoxope --quantize 6 test\/&.jpg sandbox\/&.output.quantize.jpg/' | sh

sandbox:
	cp -r test/ sandbox/

debug: build/fotoxope
	$(DBG) build/fotoxope

ifndef VERBOSE
.SILENT:
endif
