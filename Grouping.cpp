#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Grouping.h"
#include <algorithm>
#include <string>

void StockGroups::groupStocksBySurprisePercentage(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    std::getline(file, line);
    std::vector<Stock> stocks;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string token;
        Stock stock;

        std::getline(ss, stock.ticker, ',');
        std::getline(ss, token, ',');
        std::getline(ss, token, ',');
        std::getline(ss, token, ','); 
        std::getline(ss, token, ',');
        std::getline(ss, token, ','); 
        std::getline(ss, token, ',');
        stock.surprise_percentage = std::stod(token);

        stocks.push_back(stock);
    }

    file.close();

    std::sort(stocks.begin(), stocks.end(), [](const Stock& a, const Stock& b) {
        return a.surprise_percentage > b.surprise_percentage;
    });

    size_t size = stocks.size();
    size_t group_size = size / 3;

    missEstimateGroup.assign(stocks.begin(), stocks.begin() + group_size);
    meetEstimateGroup.assign(stocks.begin() + group_size, stocks.begin() + group_size * 2);
    beatEstimateGroup.assign(stocks.begin() + group_size * 2, stocks.end());
}


void StockGroups::printGroup(int groupNumber) const {
    const std::vector<Stock>* group;

    if (groupNumber == 1) {
        group = &missEstimateGroup;
    } else if (groupNumber == 2) {
        group = &meetEstimateGroup;
    } else {
        group = &beatEstimateGroup;
    }

    for (const auto& stock : *group) {
        std::cout << stock.ticker << std::endl;
    }
}

std::vector<std::string> StockGroups::getGroup(int groupNumber) const {
    const std::vector<Stock>* group;

    if (groupNumber == 1) {
        group = &missEstimateGroup;
    } else if (groupNumber == 2) {
        group = &meetEstimateGroup;
    } else {
        group = &beatEstimateGroup;
    }

    std::vector<std::string> tickers;
    for (const auto& stock : *group) {
        tickers.push_back(stock.ticker);
    }
    return tickers;
}





