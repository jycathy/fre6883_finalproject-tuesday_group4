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
            map<string, Stock_info*> StockMap;      // stores the whole set of stocks, key is the ticker and value is the pointer pointing to the Stock_info object
            map<string, Stock_info*> BeatStockMap;  // stores Beat group of stocks
            map<string, Stock_info*> MissStockMap;
            map<string, Stock_info*> MeetStockMap;
            ETF iwv;
        
        public:
            Webscraper(int N_)
            {
                N = N_;
            }
            map<string,string> GetDate(map<string,string> &Date);  // return a map with tickers as keys and announcement dates as values
            std::vector<string> GetTradingDays();  // return a vector containing all trading dates
            string GetStartDate(map<string,string> &Date,string &symbol, vector<string> &trading_dates, int N); // given the above two results and a ticker and an N, return the startDate of the stock
            string GetEndDate(map<string,string> &Date,string &symbol, vector<string> &trading_dates, int N); // return the endDate of the stock
            map<string, Stock_info*> GetBeatStockMap() {return BeatStockMap;}
            map<string, Stock_info*> GetMissStockMap() {return MissStockMap;}
            map<string, Stock_info*> GetMeetStockMap() {return MeetStockMap;}
            
            map<string, Stock_info*> GetStockMap() {return StockMap;}
            
            void getStockData(int i);  // get prices of stocks from website and do the returns calculation
            void setN(int N_) {N = N_;}
            void getIWVData(string startdate, string enddate);  // scrape IWV data and store the data into the ETF object
            void createStockMap(string filename); // create stockMap which consists of the whole set of stocks
            void clearGroupStockMap(); // clear each subgroup stockMap to avoid memory leak
        
    };
}


