#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
#include <iomanip>
#include <sstream>
#include<cmath>
#include <fstream>
#include <locale>
#include <map>
#include "curl/curl.h"


using namespace std;
namespace project{
    class Webscraper{
        private:
        int N
        
        public:
            Webscraper(N_)
            {
                N = N_
            }
            map<string,string> GetDate(map<string,string> &Date);
            std::vector<string> GetTradingDays();
            void GetStartDate(map<string,string> &Date,string &symbol, vector<string> &trading_dates， int N);
            void GetEndDate(map<string,string> &Date,string &symbol, vector<string> &trading_dates， int N);
            void getStockData();
            void getIWVData();
        
    };
}

