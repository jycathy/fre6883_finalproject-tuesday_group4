#include "Stock.h"
#include "OperatorOverloading.h"
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
            Daily_Return.push_back((Price[i]/Price[i-1] - 1)*100);
        }
    }

    void Stock_info::calCumulativeReturn()
    {
        Cumulative_Return.clear();
        //this->calDailyReturn();  // calculate daily return before calculate cumulative return
        int n = Daily_Return.size();
        Cumulative_Return.resize(n);
        //cout<<Daily_Return[0]<<endl;
        Cumulative_Return[0] = Daily_Return[0];
        for (int i=1; i<n; i++)
        {
            Cumulative_Return[i] = Cumulative_Return[i-1] + Daily_Return[i];
        }
    }
    
    void Stock_info::calAbnormalReturn(ETF etf)
    {
        Abnormal_Return.clear();
        int n = Daily_Return.size();
        Abnormal_Return.resize(n);
        Abnormal_Return = Daily_Return - etf.get_corresponding_return(start_date, end_date);
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
    
    vector<double> ETF::get_corresponding_price(string startDate, string endDate)    // startDate and endDate must be trading date
    {
        vector<double> temp;
        int m = all_dates.size();
        int beginidx=0, endidx=0;
        
        for(int i= 0; i<m; i++)
        {
            if(all_dates[i]==startDate) { beginidx = i; }
            else if(all_dates[i]==endDate) { endidx = i; }
        }
        
        for(int k=beginidx;k<=endidx; k++)
        {
            temp.push_back(Price[k]);
        }
        
        return temp;
    }
    
    vector<double> ETF::get_corresponding_return(string startDate, string endDate)
    {
        vector<double> price = this->get_corresponding_price(startDate, endDate);
        vector<double> returns;
        int m = price.size();
        for(int i=1; i < m; i++)
        {
            returns.push_back((price[i]/price[i-1] - 1)*100);
        }
        
        return returns;
    }
    
    void Stock_info::pullInfo()
    {
        std::cout << "Ticker: " << getTicker() << endl;
        std::cout << "Group: " << group << endl;
        std::cout << "Earning Announcement Date: " << announcement_date << endl;
        std::cout << "Period Ending: " << ending << endl;
        std::cout << "Estimated: " << estimate << endl;
        std::cout << "Reported earnings: " << reported << endl;
        std::cout << "Surprise: " << surprise << endl;
        std::cout << "Surprise %: " << surprise_ratio << endl;
        cout << endl;
        std::cout << "Stock Daily Prices: " << endl;
        printVector(getPrice());
        cout << endl; 
        std::cout << "Stock Cumulative Daily Returns: " << endl;
        printVector(getCumulativeReturn());
        
    }
    
}