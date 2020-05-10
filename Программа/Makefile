CC=g++
CFLAGS=-c -Wall

all: prog 

prog: main.o Data.o Server.o Client.o
	$(CC) main.o Data.o Server.o Client.o -o prog

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

Data.o: Data.hpp Data.cpp
	$(CC) $(CFLAGS) Data.hpp Data.cpp

Server.o: Server.hpp Server.cpp
	$(CC) $(CFLAGS) Server.hpp Server.cpp

Client.o: Client.hpp Client.cpp
	$(CC) $(CFLAGS) Client.hpp Client.cpp

clean:
	rm -rf *.o *.hpp.gch prog