CC = g++
CFLAGS = -Wall -ggdb3 -std=c++11 -lcurl

main: main.o Webscraper.o Grouping.o Stock.o OperatorOverloading.o GnuPlot.o Bootstrapping.o
	$(CC) $(CFLAGS) -o main main.o Webscraper.o Grouping.o Stock.o OperatorOverloading.o GnuPlot.o Bootstrapping.o
	
# Webscraper: Webscraper.o Grouping.o Stock.o OperatorOverloading.o Bootstrapping.o GnuPlot.o
# 	$(CC) $(CFLAGS) -o Webscraper Webscraper.o Grouping.o Stock.o OperatorOverloading.o Bootstrapping.o GnuPlot.o

Webscraper.o: Webscraper.cpp Webscraper.h Grouping.h Stock.h OperatorOverloading.h Bootstrapping.h
	$(CC) $(CFLAGS) -c Webscraper.cpp

Bootstrapping.o: Bootstrapping.cpp Bootstrapping.h OperatorOverloading.h Stock.h 
	$(CC) $(CFLAGS) -c Bootstrapping.cpp

Grouping.o: Grouping.cpp Grouping.h
	$(CC) $(CFLAGS) -c Grouping.cpp
	
Stock.o: Stock.cpp Stock.h
	$(CC) $(CFLAGS) -c Stock.cpp
	
OperatorOverloading.o: OperatorOverloading.cpp OperatorOverloading.h
	$(CC) $(CFLAGS) -c OperatorOverloading.cpp

GnuPlot.o: GnuPlot.cpp GnuPlot.h
	$(CC) $(CFLAGS) -c GnuPlot.cpp

clean:
	rm -rf Webscraper *.o Grouping *.o Stock *.o OperatorOverloading *.o Bootstrapping *.o GnuPlot *.o