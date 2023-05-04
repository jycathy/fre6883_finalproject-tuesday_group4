#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

struct Stock {
    std::string ticker;
    double surprise_percentage;
};

class StockGroups {
public:
    void groupStocksBySurprisePercentage(const std::string& filename);
    void printGroup(int groupNumber) const;
    const std::vector<Stock>& getGroup(int groupNumber) const;

private:
    std::vector<Stock> missEstimateGroup;
    std::vector<Stock> meetEstimateGroup;
    std::vector<Stock> beatEstimateGroup;
};

