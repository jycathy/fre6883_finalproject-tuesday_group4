#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <cmath>
#include <iterator>
#include <fstream>
#include <stdio.h>
#include <iomanip>
#include <sstream>
#include "Stock.h"
#include <map>

using namespace std;

namespace project{
    class BootStrap{
        public:
            map<string, Stock*> StockMap;
            map<string, Stock*> BeatStockMap;
            map<string, Stock*> MissStockMap;
            map<string, Stock*> BestStockMap;
            
            void createStockMap(string filename);
            
            void printStockMap()
            {
                for (map<string, Stock*>::iterator itr= StockMap.begin(); itr != StockMap.end();itr++)
    			{   
    			    cout << itr->first << endl;
    			    cout << itr->second->getAnnoucementDate() << endl;
    			}
            }
                
            
    };
}