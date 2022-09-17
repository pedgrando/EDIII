all:
	gcc -c main.c funcoes.c
	gcc -o prog main.o funcoes.o

run:   all
	./prog

clear: 
	rm main.o prog funcoes.o a.out

debug:
	gcc -g main.c funcoes.c
	gdb a.out

memcheck:
	gcc -g main.c funcoes.c
	valgrind a.out
