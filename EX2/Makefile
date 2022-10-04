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
	rm -f atv2.zip
	zip atv2.zip Makefile funcoes.h funcoes.c main.c

commit:
	git add .
	git commit -m "automatic make commit"
	git push origin main

