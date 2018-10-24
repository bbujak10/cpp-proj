main: main.o controller.o matrix.o
	g++ main.o controller.o matrix.o -o main

all: main

main.o: main.cpp
	g++ -c main.cpp -o main.o

controller.o: controller.cpp
	g++ -c controller.cpp -o controller.o

matrix.o: matrix.cpp
	g++ -c matrix.cpp -o matrix.o

clean:
	rm -f *.o