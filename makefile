all: main buffer

main: main.o
	gcc main.o -o main -I.

buffer: buffer.o
	gcc buffer.o -o buffer -I. -lm
