builds:
	rm -rf build
	mkdir build
tests:
	rm -rf build
	mkdir build
	gcc test/test.c -o build/test.out test/gfx.c src/bmpreader.c -lm -lX11 -g