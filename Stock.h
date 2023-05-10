# pragma once

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

namespace project {
    
    class Stock {
        private:
            string ticker;
            vector<double> Price;
            vector<double> Cumulative_Return;
            string group;
            string announcement_date;
            string ending;
            string estimated;
            string earnings;
            string surprise;
            string surprise_ratio;
        
        public:
            Stock(string ticker_, string date_, string ending_, string estimated_, string earnings_, string surprise_, 
                string surprise_ratio_):ticker(ticker_), announcement_date(date_), ending(ending_), surprise(surprise_), surprise_ratio(surprise_ratio_) {}
            
            void setPrice(vector<double> prices_);
            void setCumulativeReturn();
            void setGroup(string group_) {group = group_;}
            
            string getTicker() {return ticker;}
            vector<double> getPrice();
            vector<double> getCumulativeReturn();
            string getAnnoucementDate() { return announcement_date;}
            
            void pullInfo();
            
            
    };
}
