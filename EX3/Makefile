all:
	gcc -c *.c
	gcc -march=native -o prog *.o

run:   all
	./prog

clear: 
	rm *.o a.out prog

debug:
	gcc -g3 *.c -Wall -Werror -pedantic 
	gdb a.out

memcheck:
	gcc -g3 *.c -Wall -Werror -pedantic 
	valgrind --leak-check=yes ./a.out

zip:
	rm -f atv3.zip
	zip atv3.zip Makefile *.h *.c

commit:
	git pull origin main
	git add .
	git commit -m "automatic make commit"
	git push origin main

