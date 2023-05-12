# pragma once
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <map>
#include <vector>
#include "OperatorOverloading.h"
#include "Stock.h"

using namespace std;

namespace project {
    typedef vector<vector<double>> Matrix;
    
    Matrix createStockARmtx(map<string, Stock_info*> stock_map);
    
    vector<double> calculateAAR(const Matrix &ARit);
    
    
    
    
}