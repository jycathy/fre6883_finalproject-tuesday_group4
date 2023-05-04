CC = g++
CFLAGS = -Wall -ggdb3 -std=c++11 -lcurl 

Grouping: Grouping.o
	$(CC) $(CFLAGS) -o Grouping Grouping.o
	rm -f Grouping.o

Grouping.o: Grouping.cpp Grouping.h
	$(CC) $(CFLAGS) -c Grouping.cpp

clean:
	rm -rf  Grouping  *.o

