


default: build run

build:
	gcc -g main.c -o main

run:
	./main

view:
	feh -R 0.5 new.ppm -Z --force-aliasing
