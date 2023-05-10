#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

namespace fre {
    vector<double> get_daily_price();
    vector<double> cal_daily_return(vector<double> daily_price);
    vector<double> cal_cum_return(vector<double> daily_return);
    
}