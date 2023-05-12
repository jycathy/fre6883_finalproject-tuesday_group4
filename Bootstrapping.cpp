# pragma once
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <ctime>

#include "Bootstrapping.h"

using namespace std;

namespace project{
    
    Matrix createStockARmtx(map<string, Stock_info*> stock_map)
    {
        Matrix ARmtx;
        map<string, Stock_info*>::iterator itr;

        for (itr = stock_map.begin(); itr != stock_map.end(); itr++)
        {
            ARmtx.push_back((itr->second)->getAbnormalReturn());
        }
        
        return ARmtx;
    }
    
    vector<double> calculateAAR(const Matrix &ARit)
    {
        int M = ARit.size();      // number of stocks
        int N = ARit[0].size();   // number of AR
        
        vector<double> AAR(N, 0.0);
        
        for(int i=0; i<M; i++)
        { AAR = AAR + ARit[i]; }
        
        return AAR/M;
    }
    
    vector<double> calculateCAAR(const vector<double> &AAR)
    {
        double tot = 0.;
        int N = AAR.size();      // 2N days
        vector<double> result(N);
        
        for (unsigned long i = 0; i < N; i++)
        {
            tot += AAR[i];
            result[i] = tot;
        }
        
        return result;
    }
}
