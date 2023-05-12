#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
#include <iomanip>
#include <sstream>
#include<cmath>
#include <iterator>
#include <fstream>
#include <locale>
#include <map>
#include "curl/curl.h"

#include "Stock.h"
#include "Bootstrapping.h"

using namespace std;
namespace project{
    class Webscraper{
        private:
            int N;
            map<string, Stock_info*> StockMap;
            map<string, Stock_info*> BeatStockMap;
            map<string, Stock_info*> MissStockMap;
            map<string, Stock_info*> MeetStockMap;
            ETF iwv;
        
        public:
            Webscraper(int N_)
            {
                N = N_;
            }
            map<string,string> GetDate(map<string,string> &Date);
            std::vector<string> GetTradingDays();
            string GetStartDate(map<string,string> &Date,string &symbol, vector<string> &trading_dates, int N);
            string GetEndDate(map<string,string> &Date,string &symbol, vector<string> &trading_dates, int N);
            map<string, Stock_info*> GetBeatStockMap() {return BeatStockMap;}
            map<string, Stock_info*> GetMissStockMap() {return MissStockMap;}
            map<string, Stock_info*> GetMeetStockMap() {return MeetStockMap;}
            
            void getStockData();
            void getIWVData(string startdate, string enddate);
            void createStockMap(string filename);
            void clearGroupStockMap();
        
    };
}


