# pragma once

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

namespace project {
    
    class Stock_info {
        private:
            string ticker;
            vector<double> Price;
            vector<double> Daily_Return;
            vector<double> Cumulative_Return;
            string start_date;
            string end_date;
            string group;
            string announcement_date;
            string ending;
            string estimated;
            string earnings;
            string surprise;
            string surprise_ratio;
        
        public:
            Stock_info(string ticker_, string date_, string ending_, string estimated_, string earnings_, string surprise_, 
                string surprise_ratio_):ticker(ticker_), announcement_date(date_), ending(ending_), surprise(surprise_), surprise_ratio(surprise_ratio_) {}
            
            void setStartDate(string date_) { start_date = date_; }
            void setEndDate(string date_) { end_date = date_; }
            void setPrice(vector<double> prices_);
            void setGroup(string group_) {group = group_;}
            
            string getTicker() {return ticker;}
            vector<double> getPrice() {return Price;}
            vector<double> getCumulativeReturn() {return Cumulative_Return;}
            string getAnnoucementDate() { return announcement_date;}
            
            void calDailyReturn();
            void calCumulativeReturn();
            
            void printInfo()    // for test
            {
                cout<<ticker<<endl;
                int m = Price.size();
                for(int i=0; i<m; i++)
                {
                    cout<<Price[i]<<" ";
                }
                cout<<endl;
                for(int j=0; j<m-1; j++)
                {
                    cout<<Daily_Return[j]<<" ";
                }
                cout<<endl;
                for(int k=0; k<m-1; k++)
                {
                    cout<<Cumulative_Return[k]<<" ";
                }
                cout<<endl;
            }
            
            // not implemented
            void pullInfo();
            
            
    };
    
    class ETF
    {
        private:
            string ticker;
            vector<string> all_dates;
            vector<double> Price;   // price for all dates, should be of the same size as all_dates
        public:
            ETF(string ticker_):ticker(ticker_){}
            void set_all_dates(vector<string> dates_list);
            void set_Price(vector<double> prices_);       // set prices for all dates
            
            vector<string> get_all_dates() {return all_dates;}
            vector<double> get_corresponding_price(string startDate, string endDate);  // the corresponding portion of price
            vector<double> get_corresponding_return(string startDate, string endDate);  // the size should be ONE less than corresponding price
            
            
    };
    
}
