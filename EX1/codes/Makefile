all:
	gcc -c main.c funcoes.c
	gcc -march=native -o prog main.o funcoes.o

run:   all
	./prog

clear: 
	rm main.o prog funcoes.o a.out

debug:
	gcc -g3 main.c funcoes.c -Werror - pedantic -fsanitize=address,undefined
	gdb a.out

memcheck:
	gcc -g main.c funcoes.c
	valgrind a.out

zip:
	rm -f atv1.zip
	zip atv1.zip Makefile funcoes.h funcoes.c main.c
