all:
	gcc -c main.c funcoes.c funcoes_reg.c funcoes_header.c funcoes_bin.c
 	gcc -march=native -o prog main.o funcoes.o funcoes_reg.o funcoes_header.o funcoes_bin.o

run:   all
	./prog

clear: 
	rm main.o prog funcoes.o funcoes_reg.o funcoes_header.o funcoes_bin.o a.out

debug:
	gcc -g3 main.c funcoes.c funcoes_reg.c funcoes_header.c funcoes_bin.c -Wall -Werror -pedantic 
	gdb a.out

memcheck:
	gcc -g main.c funcoes.c funcoes_reg.c funcoes_header.c funcoes_bin.c
	valgrind a.out

zip:
	rm -f atv2.zip
	zip atv2.zip Makefile funcoes.h funcoes.c funcoes_reg.c funcoes_header.c funcoes_bin.c main.c

commit:
	git pull origin main
	git add .
	git commit -m "automatic make commit"
	git push origin main

