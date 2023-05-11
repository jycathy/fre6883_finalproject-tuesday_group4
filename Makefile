CC = g++
CFLAGS = -Wall -ggdb3 -std=c++11 -lcurl

Webscraper: Webscraper.o Grouping.o Stock.o OperatorOverloading.o
	$(CC) $(CFLAGS) -o Webscraper Webscraper.o Grouping.o Stock.o OperatorOverloading.o

Webscraper.o: Webscraper.cpp Webscraper.h Grouping.h Stock.h OperatorOverloading.h
	$(CC) $(CFLAGS) -c Webscraper.cpp

Grouping.o: Grouping.cpp Grouping.h
	$(CC) $(CFLAGS) -c Grouping.cpp
	
Stock.o: Stock.cpp Stock.h
	$(CC) $(CFLAGS) -c Stock.cpp
	
OperatorOverloading.o: OperatorOverloading.cpp OperatorOverloading.h
	$(CC) $(CFLAGS) -c OperatorOverloading.cpp

clean:
	rm -rf Webscraper *.o Grouping *.o Stock *.o OperatorOverloading *.o