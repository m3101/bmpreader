builds:
	rm -rf build
	mkdir build
	gcc -c -Wall -Werror -fpic src/bmpreader.c -o build/bmpreader.o
	gcc -shared -o build/libbmpreader.so build/bmpreader.o
tests:
	rm -rf build
	mkdir build
	gcc test/test.c -o build/test.out test/gfx.c src/bmpreader.c -lm -lX11 -g