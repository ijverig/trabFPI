build/fotoxope: src/fotoxope.c src/image.c src/transformations.c
	mkdir -p build
	gcc -std=c99 -g -Wall -Wno-deprecated-declarations -o build/fotoxope src/fotoxope.c src/image.c src/transformations.c

.PHONY: clean run
clean:
	rm -rf build sandbox

run: build/fotoxope
	build/fotoxope test/Underwater_53k.jpg build/output_image.jpg

test: build/fotoxope
	cp -r test/ sandbox/
	ls -1 test/ | sed 's/.jpg*//' | sed 's/.*/build\/fotoxope test\/&.jpg sandbox\/&.output.jpg/' | sh

debug: build/fotoxope
	lldb build/fotoxope test/Underwater_53k.jpg build/output_image.jpg
