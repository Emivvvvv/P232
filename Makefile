all: p232

p232: main.o P_header.o
	gcc -o p232.out main.o P_header.o

main.o: main.c P_header.h
	gcc -c main.c

P_header.o: P_header.c P_header.h
	gcc -c P_header.c

clean:
	rm -f *.o p232.out
