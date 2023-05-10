CC = g++
CFLAGS = -Wall -ggdb3 -std=c++11 -lcurl

Webscraper: Webscraper.o Grouping.o Stock.o
	$(CC) $(CFLAGS) -o Webscraper Webscraper.o Grouping.o Stock.o

Webscraper.o: Webscraper.cpp Webscraper.h Grouping.h Stock.h
	$(CC) $(CFLAGS) -c Webscraper.cpp

Grouping.o: Grouping.cpp Grouping.h
	$(CC) $(CFLAGS) -c Grouping.cpp
	
Stock.o: Stock.cpp Stock.h
	$(CC) $(CFLAGS) -c Stock.cpp

clean:
	rm -rf Webscraper *.o