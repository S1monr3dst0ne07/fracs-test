


default: build run

build: mandel.c
	gcc -g mandel.c -o mandel

run:
	./mandel
