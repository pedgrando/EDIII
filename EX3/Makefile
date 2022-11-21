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
	gcc -g *.c
	valgrind a.out

zip:
<<<<<<< HEAD
	rm -f atv2.zip
	zip atv2.zip Makefile *.h *.c
=======
	rm -f atv3.zip
	zip atv3.zip Makefile *.h *.c
>>>>>>> 3232f41462f2656ad959c1414b3144c4cd146683

commit:
	git pull origin main
	git add .
	git commit -m "automatic make commit"
	git push origin main

