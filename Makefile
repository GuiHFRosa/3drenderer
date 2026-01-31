CC = gcc
CFLAGS = -Wall -std=c99 $(shell sdl2-config --cflags)
LDFLAGS = $(shell sdl2-config --libs)

build:
	$(CC) $(CFLAGS) ./src/*.c $(LDFLAGS)  -o renderer

run:
	./renderer

clean:
	rm renderer
