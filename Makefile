build/fotoxope: src/fotoxope.c
	mkdir -p build
	gcc -std=c99 -Wall -Wno-deprecated-declarations -o build/fotoxope src/fotoxope.c

.PHONY: clean test
clean:
	rm -rf build

test: build/fotoxope
	build/fotoxope test/Underwater_53k.jpg build/output_image.jpg
