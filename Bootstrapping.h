# pragma once
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <map>
#include <vector>
#include <utility>
#include "OperatorOverloading.h"
#include "Stock.h"

using namespace std;

namespace project {
    typedef vector<vector<double>> Matrix;
    
    Matrix createStockARmtx(map<string, Stock_info*> stock_map);  // generate AR matrix of all stocks from stock map
    Matrix genSelectedARmtx(Matrix ARmtx, int M);  // generate AR matrix of M randomly picked stocks from whole AR matrix
    
    vector<double> calculateAAR(const Matrix &ARit);  // generate AAR vector from the AR matrix
    vector<double> calculateCAAR(const vector<double> &AAR);  // generate CAAR vector from the AR matrix
    
    Matrix Bootstrapping(map<string, Stock_info*> stock_map, int M, int N);  // return the matrix of AAR, AAR_STD, CAAR, CAAR_STD
    
    
}