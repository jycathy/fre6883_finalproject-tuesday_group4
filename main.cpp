#include <iostream>
#include "Webscraper.h"
#include "Grouping.h"
#include "OperatorOverloading.h"
#include "Stock.h"
#include "GnuPlot.h"
#include <chrono>
#include <thread>
#include <vector>
#include "Bootstrapping.h"

using namespace std;
using namespace project;

string validatestring(string tick)
{
	string t;
	char c; 
	int i = 0;
	if (tick.back() != '\0')
	{
		tick.push_back('\0');
	}
	
	while (tick[i] != '\0')
	{
		c = tick[i];
		if (islower(c)) 
			c = toupper(c);
		t.push_back(c);
		i++;
	}
	return t;
}

int printVector(vector<double> V)
{
	for(vector<double> :: iterator itr = V.begin(); itr != V.end(); itr++)
	{
		cout << *itr << "  ";
	}
	cout << endl;
	return 0;
}
          
typedef vector<Matrix> newMatrix;

int main()
{   
    
    std::chrono::time_point<std::chrono::system_clock> start, end;
    int input = 0;
    int N = 0;
    int Group;
    int count;
    string tick;
    
    Webscraper Scraper(N);

	Scraper.createStockMap("Russell3000EarningsAnnouncements.csv");
	Scraper.getIWVData("2022-01-03","2023-05-04");
    
    Matrix resultForBeatGroup;
	Matrix resultForMeetGroup;
	Matrix resultForMissGroup;
	
	newMatrix finalMatrix(3);
    
    GnuPlot gnuplot;
    
    while (input != 5)
	{
		cout << "Menu:" << endl;
		cout << "Enter 1 to Retrieve price data for all stocks " << endl;
		cout << "Enter 2 to Pull Individual Stock Data" << endl;
		cout << "Enter 3 to Show Group Data" << endl;
		cout << "Enter 4 to Plot Returns" << endl;
		cout << "Enter 5 to Exit" << endl;
		cout << "Enter Your Choice and Press Return: " << " ";

		cin >> input;
		cout << endl;
		
		switch(input)
		{
		case 1:
		{
			cout << "Enter the number of the days: ";
			cin >> N;
			if (N < 60)
			// if (N < 2)
			{
				cout << "The days to retrieve data should be at least 60" << endl;
				continue;
			}
		
			else
			{
				Scraper.setN(N);
				
				start = std::chrono::system_clock::now();
				cout << "Now starting to populate the stock map: " << endl;
				// Scraper.PopulateMultiThread();
				Scraper.getStockData();
				end = std::chrono::system_clock::now();
				cout << "Stock map completed!" << endl;
				
				std::chrono::duration<double> elapsed_seconds = end - start;
				std::cout << "Time taken for Data Retrieval: " << elapsed_seconds.count() << "s\n";

				std::time_t end_time = std::chrono::system_clock::to_time_t(end);
				std::cout << "Finished computation at " << std::ctime(&end_time) << endl;

				cout << "The number of Stocks in Beat Group is : " << Scraper.GetBeatStockMap().size() << endl;

				cout << "The number of Stocks in Meet Group is : " << Scraper.GetMeetStockMap().size() << endl;

				cout << "The number of Stocks in Miss Group is : " << Scraper.GetMissStockMap().size() << endl;

				break;
			}
		}
		
		case 2:
		{
			if (Scraper.GetStockMap().empty())
			{
				cout << "The Map has not been populated yet, please select option 1 to create and populate stock map first:" << endl;
				break;
			}

			cout << "Enter the stock ticker to pull out the data:" << endl;
			
			cin >> tick;

			string s = validatestring(tick);
			Scraper.GetStockMap()[s]->pullInfo();
			break;
		}
		
		case 3:
		{
			if (Scraper.GetStockMap().empty())
			{
				cout << "The Map has not been populated yet, please select option 1 to create and populate stock map first:" << endl;
				break;
			}
			
			// cout << "Enter Group (Beat, Meet, Miss) for more information: " << endl;
			cout << "Enter 1 to see information for Beat Group" << endl;
			cout << "Enter 2 to see information for Meet Group" << endl;
			cout << "Enter 3 to see information for Miss Group" << endl;
			cout << "Enter your choice: ";
			cin >> Group;
			
			if (Group != 1 && Group != 2 && Group != 3)
        	{
            	cerr << "Invalid selection." << endl;
            	break;
        	}
			
			resultForBeatGroup = Bootstrapping(Scraper.GetBeatStockMap(), 80, 40);
			resultForMeetGroup = Bootstrapping(Scraper.GetMeetStockMap(), 80, 40);
			resultForMissGroup = Bootstrapping(Scraper.GetMissStockMap(), 80, 40);
			
			int m = resultForBeatGroup.size(); // 4
			int n = resultForBeatGroup[0].size();  // 2N
			
			// newMatrix finalMatrix(3);
			
			for(int i=0;i<3;i++)
			{
				finalMatrix[i].resize(4);
			}
			
			for(int i=0;i<m;i++)
			{
				finalMatrix[0][i] = resultForBeatGroup[i]; 
				finalMatrix[1][i] = resultForMeetGroup[i]; 
				finalMatrix[2][i] = resultForMissGroup[i]; 
			}
			
			cout<<endl;
			
			switch (Group) 
			{
				
				case 1:
					count = 0;
					cout << "*********** Beat Group **************" << endl;
					for (vector<vector<double>> :: iterator itr = finalMatrix[0].begin(); itr != finalMatrix[0].end(); itr++)
					{
						count += 1;
						if (count == 1)
						{
							cout << "Average AARs for Beat Group: ";
							cout << endl;
						}
						else if (count == 2)
						{
							cout << "STD AARs for Beat Group: ";
							cout << endl;
						}
						else if (count == 3)
						{
							cout << "Average CAARs for Beat Group: ";
							cout << endl;
						}
						else
						{
							cout << "STD CAARs for Beat Group: ";
							cout << endl;
						}
						printVector(*itr);
					}
					break;
				
				case 2:
					count = 0;
					cout << "*********** Meet Group **************" << endl;
					for (vector<vector<double>> :: iterator itr = finalMatrix[1].begin(); itr != finalMatrix[1].end(); itr++)
					{
						count += 1;
						if (count == 1)
						{
							cout << "Average AARs for Meet Group: ";
							cout << endl;
						}
						else if (count == 2)
						{
							cout << "STD AARs for Meet Group: ";
							cout << endl;
						}
						else if (count == 3)
						{
							cout << "Average CAARs for Meet Group: ";
							cout << endl;
						}
						else
						{
							cout << "STD CAARs for Meet Group: ";
							cout << endl;
						}
						printVector(*itr);
					}
					break;
				
				case 3:
					count = 0;
					cout << "*********** Miss Group **************" << endl;
					for (vector<vector<double>> :: iterator itr = finalMatrix[2].begin(); itr != finalMatrix[2].end(); itr++)
					{
						count += 1;
						if (count == 1)
						{
							cout << "Average AARs for Miss Group: ";
							cout << endl;
						}
						else if (count == 2)
						{
							cout << "STD AARs for Miss Group: ";
							cout << endl;
						}
						else if (count == 3)
						{
							cout << "Average CAARs for Miss Group: ";
							cout << endl;
						}
						else
						{
							cout << "STD CAARs for Miss Group: ";
							cout << endl;
						}
						printVector(*itr);
					}
					break;
			}
			break;
		}
		
		case 4:
		{
			cout << "set private data" << endl;
			gnuplot.setData1(finalMatrix[0][2]);
			gnuplot.setData2(finalMatrix[1][2]);
			gnuplot.setData3(finalMatrix[2][2]);
			cout << "showing plot results" << endl;
			gnuplot.plotResults();
			break;
		}
		
		case 5: 
			break;
		
		default:
			cout << "Please enter a valid input." << endl;
			break;
		
		}
		
	}
	
	curl_global_cleanup();
	
	return 0;
}