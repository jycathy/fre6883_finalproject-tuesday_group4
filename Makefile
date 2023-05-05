CC = g++
CFLAGS = -Wall -ggdb3 -std=c++11 -lcurl

Webscraper: Webscraper.o Grouping.o
	$(CC) $(CFLAGS) -o Webscraper Webscraper.o Grouping.o

Webscraper.o: Webscraper.cpp Webscraper.h Grouping.h
	$(CC) $(CFLAGS) -c Webscraper.cpp

Grouping.o: Grouping.cpp Grouping.h
	$(CC) $(CFLAGS) -c Grouping.cpp

clean:
	rm -rf Webscraper *.o