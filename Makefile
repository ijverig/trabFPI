OS := $(shell uname)

CC     = cc
DBG    = lldb
CFLAGS = -std=c99 -g -Wall -Wno-deprecated-declarations
ifeq ($(OS), Linux)
	DBG = gdb
endif

CLISRC   = $(wildcard src/CLI/*.c)
CLIHEAD  = $(CLISRC:.c=.h)
CORESRC  = $(wildcard src/core/*.c)
COREHEAD = $(CORESRC:.c=.h)

build/fotoxope: build/fotoxopeCLI

build/fotoxopeCLI: src/fotoxopeCLI.c $(CLISRC) $(CORESRC)
	mkdir -p build
	$(CC) $(CFLAGS) -o $@ $^

src/fotoxopeCLI.c: $(CLIHEAD) $(COREHEAD)

.PHONY: clean test
clean:
	rm -rf build sandbox

test: version fliph flipv gray quantize commqueue

version: build/fotoxopeCLI
	build\/fotoxopeCLI -v src/version.h && \
	build\/fotoxopeCLI --version src/version.h

fliph: build/fotoxopeCLI sandbox
	ls -1 test/ | sed 's/.jpg*//' | sed 's/.*/build\/fotoxopeCLI -F h test\/&.jpg sandbox\/&.output.fliph.jpg/' | sh && \
	ls -1 test/ | sed 's/.jpg*//' | sed 's/.*/build\/fotoxopeCLI --flip horizontal test\/&.jpg sandbox\/&.output.fliph.jpg/' | sh

flipv: build/fotoxopeCLI sandbox
	ls -1 test/ | sed 's/.jpg*//' | sed 's/.*/build\/fotoxopeCLI -F v test\/&.jpg sandbox\/&.output.flipv.jpg/' | sh && \
	ls -1 test/ | sed 's/.jpg*//' | sed 's/.*/build\/fotoxopeCLI --flip vertical test\/&.jpg sandbox\/&.output.flipv.jpg/' | sh

gray: build/fotoxopeCLI sandbox
	ls -1 test/ | sed 's/.jpg*//' | sed 's/.*/build\/fotoxopeCLI -G test\/&.jpg sandbox\/&.output.gray.jpg/' | sh && \
	ls -1 test/ | sed 's/.jpg*//' | sed 's/.*/build\/fotoxopeCLI --gray test\/&.jpg sandbox\/&.output.gray.jpg/' | sh

quantize: build/fotoxopeCLI sandbox
	ls -1 test/ | sed 's/.jpg*//' | sed 's/.*/build\/fotoxopeCLI -Q 6 test\/&.jpg sandbox\/&.output.quantize.jpg/' | sh && \
	ls -1 test/ | sed 's/.jpg*//' | sed 's/.*/build\/fotoxopeCLI --quantize 6 test\/&.jpg sandbox\/&.output.quantize.jpg/' | sh

commqueue: build/fotoxopeCLI sandbox
	build\/fotoxopeCLI -G -G -G -G -G -G -G -G -G -G -G -G -G -G -G -G test/Underwater_53k.jpg sandbox/-void.jpg	&& \
	build\/fotoxopeCLI -G -G -G -G -G -G -G -G -G -G -G -G -G -G -G -G -G test/Underwater_53k.jpg sandbox/-void.jpg && \
	build\/fotoxopeCLI -G -G -G -G -G -G -G -G -G -G -G -G -G -G -G -G -G -G test/Underwater_53k.jpg sandbox/-void.jpg

sandbox:
	cp -r test/ sandbox/

debug: build/fotoxopeCLI
	$(DBG) build/fotoxopeCLI

ifndef VERBOSE
.SILENT:
endif
