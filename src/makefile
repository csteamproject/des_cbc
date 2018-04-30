all: main.o desutils.o
	g++ main.o desutils.o -o main

main.o: main.cpp
	g++ -c main.cpp

part2: part2.o desutils.o program3utils.o
	g++ part2.o desutils.o program3utils.o -o part2 -I/usr/local/ssl/include -L/usr/local/ssllib -lssl -lcrypto

part2.o: part2.cpp
	g++ -c part2.cpp

program3utils.o: program3utils.cpp program3utils.h
	g++ -c program3utils.cpp

desutils.o: desutils.cpp desutils.h
	g++ -c desutils.cpp

clean:
	rm *.o
	rm sessionkey.txt
