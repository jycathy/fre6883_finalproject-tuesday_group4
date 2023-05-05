#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;
namespace project{
    struct Stock {
        string ticker;
        double surprise_percentage;
    };

    class StockGroups {
    public:
        void groupStocksBySurprisePercentage(const std::string& filename);
        std::vector<Stock> printGroup(int groupNumber) const;
        std::vector<std::string> getGroup(int groupNumber) const;

    private:
        std::vector<Stock> missEstimateGroup;
        std::vector<Stock> meetEstimateGroup;
        std::vector<Stock> beatEstimateGroup;
    };
}


