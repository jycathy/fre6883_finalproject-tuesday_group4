#include <iostream>
#include "Bootstrap.h"
#include "Stock.h"
#include <string>
#include <vector>
#include<algorithm>
#include <iterator>
#include <cmath>

using namespace std;

namespace project{
    void BootStrap::createStockMap(string filename)
	{
		ifstream ifile;
		ifile.open(filename, ios::in);
		if (!ifile.is_open())
			cout << "Error file not opened" << endl;
		//else
			//cout << "open" << endl;
		string line, word;
		vector<string> row;
		ifile.ignore(10000, '\n');
		while (!ifile.eof())
		{
			row.clear();

			getline(ifile, line);
			if (!line.empty()) {

				stringstream s(line);

				while (getline(s, word, ','))
				{
					row.push_back(word);
				}
				
				Stock* st = new Stock(row[0], row[1], row[2], row[3], row[4], row[5], row[6]);
				StockMap.insert(pair<string, Stock*>(row[0], st));
			}

		}
		ifile.close();

	}
	
	

}

int main(){
    project::BootStrap test;
    test.createStockMap("Russell3000EarningsAnnouncements.csv");
    test.printStockMap();
    return 0;
	}
