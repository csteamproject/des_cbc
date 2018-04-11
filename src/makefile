all: main.o desutils.o
	g++ main.o desutils.o -o main

main.o: main.cpp
	g++ -c main.cpp

desutils.o: desutils.cpp desutils.h
	g++ -c desutils.cpp

clean:
	rm *.o main
