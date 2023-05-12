# pragma once
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>

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
    
    Matrix genSelectedARmtx(Matrix ARmtx, int M)     // randomly pick M AR and generate a M*2N matrix
    {
        int totalSize = ARmtx.size();   // total number of stocks
        // generate indices of randomly picked stocks
        vector<int> indices;
        while ((int)indices.size() < M)
        {
            int index = rand() % totalSize;
            //cout<<index<<" ";
            
            if (std::find(indices.begin(), indices.end(), index) == indices.end())
            {
                // Not in the indices. Add it
                indices.push_back(index);
            }
        }
        
        Matrix mtx;
        for (const int &index : indices)
        {
            mtx.push_back(ARmtx[index]);
        }
        //cout<<mtx.size()<<endl;
        return mtx;
        
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
        
        for (int i = 0; i < N; i++)
        {
            tot += AAR[i];
            result[i] = tot;
        }
        
        return result;
    }
}
