all: main.o desutils.o
	g++ main.o desutils.o -o main

main.o: main.cpp
	g++ -c main.cpp

part2: part2.o desutils.o
	g++ part2.o desutils.o -o part2

part2.o: part2.cpp
	g++ -c part2.cpp

desutils.o: desutils.cpp desutils.h
	g++ -c desutils.cpp

clean:
	rm *.o
