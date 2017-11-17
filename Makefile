build/fotoxope: src/fotoxope.c src/image.c
	mkdir -p build
	gcc -std=c99 -Wall -Wno-deprecated-declarations -o build/fotoxope src/fotoxope.c src/image.c

.PHONY: clean test
clean:
	rm -rf build

test: build/fotoxope
	build/fotoxope test/Underwater_53k.jpg build/output_image.jpg
