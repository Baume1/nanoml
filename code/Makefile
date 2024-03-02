all: main clean

main: main.o
	gcc -o main main.o -Wall -Wextra

main.o: main.c
	gcc -c main.c -Wall -Wextra

clean:
	del *.o 
