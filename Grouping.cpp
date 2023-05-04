#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Grouping.h"
#include <algorithm>
#include <string>
using namespace std;

namespace project{
    void StockGroups::groupStocksBySurprisePercentage(const std::string& filename) {
        ifstream file(filename);
        string line;
        getline(file, line);
        vector<Stock> stocks;

        while (getline(file, line)) {
            stringstream ss(line);
            string token;
            Stock stock;

            getline(ss, stock.ticker, ',');
            getline(ss, token, ',');
            getline(ss, token, ',');
            getline(ss, token, ','); 
            getline(ss, token, ',');
            getline(ss, token, ','); 
            getline(ss, token, ',');
            stock.surprise_percentage = std::stod(token);

            stocks.push_back(stock);
        }

        file.close();

        sort(stocks.begin(), stocks.end(), [](const Stock& a, const Stock& b) {
            return a.surprise_percentage > b.surprise_percentage;
        });

        size_t size = stocks.size();
        size_t group_size = size / 3;

        missEstimateGroup.assign(stocks.begin(), stocks.begin() + group_size);
        meetEstimateGroup.assign(stocks.begin() + group_size, stocks.begin() + group_size * 2);
        beatEstimateGroup.assign(stocks.begin() + group_size * 2, stocks.end());
    }


    void StockGroups::printGroup(int groupNumber) const {
        const vector<Stock>* group;

        if (groupNumber == 1) {
            group = &missEstimateGroup;
        } else if (groupNumber == 2) {
            group = &meetEstimateGroup;
        } else {
            group = &beatEstimateGroup;
        }

        for (const auto& stock : *group) {
            cout << stock.ticker << std::endl;
        }
    }

    vector<std::string> StockGroups::getGroup(int groupNumber) const {
        const std::vector<Stock>* group;

        if (groupNumber == 1) {
            group = &missEstimateGroup;
        } else if (groupNumber == 2) {
            group = &meetEstimateGroup;
        } else {
            group = &beatEstimateGroup;
        }

        vector<std::string> tickers;
        for (const auto& stock : *group) {
            tickers.push_back(stock.ticker);
        }
        return tickers;
    }
}




