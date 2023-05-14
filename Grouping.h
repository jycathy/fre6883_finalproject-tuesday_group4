#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;
namespace project{
    // Define Stock structure to hold stock data
    struct Stock {
        string ticker; // Stock ticker
        double surprise_percentage; // Surprise percentage of the stock
    };

    class StockGroups {
    public:
        void groupStocksBySurprisePercentage(const std::string& filename);
        std::vector<Stock> printGroup(int groupNumber) const;
        std::vector<std::string> getGroup(int groupNumber) const;

    private:
        // Vectors to hold each group of stocks
        std::vector<Stock> missEstimateGroup;
        std::vector<Stock> meetEstimateGroup;
        std::vector<Stock> beatEstimateGroup;
    };
}


