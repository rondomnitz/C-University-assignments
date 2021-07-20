mycomp :  mycomp.o complex.o input_check.o
	gcc -g -ansi -Wall -pedantic mycomp.o complex.o input_check.o -o mycomp -lm

mycomp.o:  mycomp.c complex.h
	gcc -c -ansi -Wall -pedantic mycomp.c -o mycomp.o

complex.o:  complex.c complex.h
	gcc -c -ansi -Wall -pedantic complex.c -o complex.o -lm
	
input_check.o:  input_check.c complex.h
	gcc -c -ansi -Wall -pedantic input_check.c -o input_check.o