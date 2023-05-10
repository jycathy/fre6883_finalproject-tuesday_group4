#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

namespace project {
    vector<double> cal_daily_return(vector<double> daily_price);
    vector<double> cal_cum_return(vector<double> daily_return);
    
}