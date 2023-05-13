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
    
    Matrix Bootstrapping(map<string, Stock_info*> stock_map, int M, int N)    // select M stocks, repeat N times
    {
        Matrix resultMtx;
        Matrix totalARmtx = createStockARmtx(stock_map);
        int nofd = totalARmtx[0].size();  // number of days, i.e. 2N
        cout<<nofd<<endl;
        vector<double> AverageAAR(nofd,0.0), AAR_STD(nofd,0.0), AverageCAAR(nofd,0.0), CAAR_STD(nofd,0.0);
        Matrix AARgenerated, CAARgenerated;
        
        for(int i=0; i<N; i++)
        {
            // select M stocks from totalATmtx
            Matrix selectedARmtx = genSelectedARmtx(totalARmtx, M);
            // calculate AAR of the group
            vector<double> AAR = calculateAAR(selectedARmtx);
            AARgenerated.push_back(AAR);
            // calculate CAAR of the group
            vector<double> CAAR = calculateCAAR(AAR);
            CAARgenerated.push_back(CAAR);
            // Average AAR
            AverageAAR = (i * AverageAAR + AAR) / (i + 1);
            // Average CAAR
            AverageCAAR = calculateCAAR(AverageAAR);
        }
        
        resultMtx.push_back(AverageAAR);
        
        // calculate AAR STD
        for(int i=0; i<N; i++)
        {
            AAR_STD = (i * AAR_STD + ((AARgenerated[i] - AverageAAR) * (AARgenerated[i] - AverageAAR))) / (i + 1);
        }
        
        resultMtx.push_back(AAR_STD);
        
        resultMtx.push_back(AverageCAAR);
        
        // calculate CAAR STD
        for(int i=0; i<N; i++)
        {
            CAAR_STD = (i * CAAR_STD + ((CAARgenerated[i] - AverageCAAR) * (CAARgenerated[i] - AverageCAAR))) / (i + 1);
        }
        
        resultMtx.push_back(CAAR_STD);
        
        return resultMtx;
        
    }
}
