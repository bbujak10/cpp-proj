main: main.o tree.o
	g++ main.o tree.o -o main

all: main

main.o: main.cpp
	g++ -c main.cpp -o main.o

tree.o: tree.cpp
	g++ -c tree.cpp -o tree.o

clean:
	rm -f *.o