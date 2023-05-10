#include "Stock.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>

using namespace std;

namespace project{
    
    void Stock_info::setPrice(vector<double> prices_)
    {
        int m = prices_.size();
        Price.clear();
        for(int i=0; i<m; i++)
        {
            Price.push_back(prices_[i]);
        }
    }
    
    void Stock_info::calDailyReturn()
    {
        Daily_Return.clear();   // each time recalculate return, clear the current one
        int m = Price.size();
        for(int i=1; i < m; i++)
        {
            Daily_Return.push_back(Price[i]/Price[i-1] - 1);
        }
    }

    void Stock_info::calCumulativeReturn()
    {
        Cumulative_Return.clear();
        this->calDailyReturn();  // calculate daily return before calculate cumulative return
        int n = Daily_Return.size();
        Cumulative_Return.resize(n);
        Cumulative_Return.push_back(Daily_Return[0]);
        for (int i=1; i<n; i++)
        {
            Cumulative_Return[i] = Cumulative_Return[i-1] + Daily_Return[i];
        }
    }
    
    void ETF::set_all_dates(vector<string> dates_list)
    {
        int m = dates_list.size();
        all_dates.clear();
        for(int i=0; i<m; i++)
        {
            all_dates.push_back(dates_list[i]);
        }
    }
    
    void ETF::set_Price(vector<double> prices_)
    {
        int m = prices_.size();
        Price.clear();
        for(int i=0; i<m; i++)
        {
            Price.push_back(prices_[i]);
        }
    }
    
    void ETF::clearData()
    {
        all_dates.clear();
        Price.clear();
    }
    
}