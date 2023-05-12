#include <iostream>
#include "Webscraper.h"
#include "Grouping.h"
#include "OperatorOverloading.h"
#include "Stock.h"
#include <chrono>
#include <thread>

string validatestring(string tick)
{
	string t;
	if (tick.back() != '\0') tick.push_back('\0');
	char c; int i = 0;
	while (tick[i] != '\0')
	{
		c = tick[i];
		if (islower(c)) c = toupper(c);
		t.push_back(c);
		i++;
	}
	return t;
}



int main()
{   
    
    
    std::chrono::time_point<std::chrono::system_clock> start, end;
    int input = 0;
    int N = 0;
    project::Webscraper Scraper(N);
    
    // Scraper.getN();
    // Scraper.createStockMap("Russell3000EarningsAnnouncements.csv");
    //Scraper.getStockData();
    // Scraper.getIWVData("2023-03-01","2023-03-10");
    
    
    
    
    while (input != 5)
	{
		cout << "Menu" << endl;
		cout << "Enter 1 to Retrieve price data for all stocks " << endl;
		cout << "Enter 2 to Pull Individual Stock Data" << endl;
		cout << "Enter 3 to Show Group Data" << endl;
		cout << "Enter 4 to Plot Returns" << endl;
		cout << "Enter 5 to Exit: " << endl;

		cin >> input;
		switch(input)
		{
		case 1:
// 			
			cout << "Enter the Number of the days for which the stock Data Needs to be populated" << endl;
			cin >> N;
			if (N < 60 || N>90)
			{
				cout << "The days to retrieve data should be atleast 60 but less than 90" << endl;
				break;
			}
// 			
			else
			{
				Scraper.setN(N);
				
				start = std::chrono::system_clock::now();
				cout << "Now starting to Populate the stock map with prices: " << endl;
				// Scraper.PopulateMultiThread();
				Scraper.createStockMap("Russell3000EarningsAnnouncements.csv");
				Scraper.getStockData();
				end = std::chrono::system_clock::now();
				
				std::chrono::duration<double> elapsed_seconds = end - start;
				// std::cout << "Data Retrieval elapsed time: " << elapsed_seconds.count() << "s\n";
				
				// beatEstimateGroup.clearGroupStockMap();
				// meetEstimateGroup.clearGroupStockMap();
				// missEstimateGroup.clearGroupStockMap();

				// std::time_t end_time = std::chrono::system_clock::to_time_t(end);
				// std::cout << "finished computation at " << std::ctime(&end_time) << endl;

				cout << "The number of Stocks in Beat Group is : " << Scraper.GetBeatStockMap().size() << endl;

				cout << "The number of Stocks in Meet Group is : " << Scraper.GetMeetStockMap().size() << endl;

				cout << "The number of Stocks in Miss Group is : " << Scraper.GetMissStockMap().size() << endl;

				break;
			}
			
		// case 2:
		// 	if (Scraper.getStockMap().empty())
		// 	{
		// 		cout << "The Map has not yet been populated for the first time, please select option 1 to create and populate stock map first:" << endl;
		// 		break;
		// 	}

		// 	cout << "Enter the stock ticker to pull out the data:" << endl;
		// 	string tick;
		// 	cin >> tick;

		// 	string s = validatestring(tick);
		// 	Scraper.getStockMap()[s]->pullInfo();
		// 	break;
		
		
		
		
		case 5: 
			break;
		
		}
	}
	return 0;
}