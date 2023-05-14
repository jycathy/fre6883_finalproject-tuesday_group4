#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Grouping.h"
#include <algorithm>
#include <string>
using namespace std;

namespace project{
    // Reads a file and groups stocks into three categories based on surprise percentage
    void StockGroups::groupStocksBySurprisePercentage(const std::string& filename) {
        ifstream file(filename);  // Open the file
        string line;
        getline(file, line); // Read the first line
        vector<Stock> stocks; // Use vector to hold all stocks
        
        // Loop over each line in the file
        while (getline(file, line)) {
            stringstream ss(line); // Use stringstream to split the line
            string token; // Temporary string to hold each field in a line
            Stock stock;
            
            getline(ss, stock.ticker, ','); // Store ticker
            getline(ss, token, ','); // Skip next five fields
            getline(ss, token, ',');
            getline(ss, token, ','); 
            getline(ss, token, ',');
            getline(ss, token, ','); 
            getline(ss, token, ',');
            stock.surprise_percentage = std::stod(token); // Convert string to double and store surprise percentage

            stocks.push_back(stock); // Add the stock to the vector
        }

        file.close();
        // Sort the stocks in ascending order based on surprise percentage
        sort(stocks.begin(), stocks.end(), [](const Stock& a, const Stock& b) {
            return a.surprise_percentage < b.surprise_percentage;
        });

        size_t size = stocks.size();
        size_t group_size = size / 3;

        missEstimateGroup.assign(stocks.begin(), stocks.begin() + group_size);
        meetEstimateGroup.assign(stocks.begin() + group_size, stocks.begin() + group_size * 2);
        beatEstimateGroup.assign(stocks.begin() + group_size * 2, stocks.end());
    }
    
    vector<Stock> StockGroups::printGroup(int groupNumber) const {
        const vector<Stock>* group; // Pointer to the group to be returned
        
        if (groupNumber == 1) {
            group = &beatEstimateGroup;
        } else if (groupNumber == 2) {
            group = &meetEstimateGroup;
        } else {
            group = &missEstimateGroup;
        }

        for (const auto& stock : *group) {
            cout << stock.ticker << std::endl;
        }
    }

    vector<string> StockGroups::getGroup(int groupNumber) const {
        const std::vector<Stock>* group; // Pointer to the group to be returned

        if (groupNumber == 1) {
            group = &beatEstimateGroup;
        } else if (groupNumber == 2) {
            group = &meetEstimateGroup;
        } else {
            group = &missEstimateGroup;
        }

        vector<std::string> tickers; // Vector to hold the tickers of the stocks in the group
        for (const auto& stock : *group) {
            tickers.push_back(stock.ticker);
        }
        return tickers; // Return the vector of tickers
    }
}




