#include <iostream>
#include <string>
#include <vector>
#include "calculation.h"
using namespace std;
namespace fre {
    vector<double> get_daily_price();
    
    vector<double> cal_daily_return(vector<double> daily_price)
    {
        int d = (int)daily_price.size();
        vector<double> daily_return(d-1);
        for( int i = 1; i < d; i++ ){
            daily_return[i-1] = (daily_price[i] - daily_price[i-1]) / daily_price[i-1];
        }
        return daily_return;
    }
    
    vector<double> cal_cum_return(vector<double> daily_return){
        int d = (int)daily_return.size();
        vector<double> cum_return(d);
        for( int i = 1; i < d; i++ ){
            cum_return[i] += cum_return[i-1];
        }
        return cum_return;
    }
    
    vector operator-(const vector& V, const vector& W)
    {
        int d = (int)V.size();
        vector U(d);
        for (int j = 0; j < d; j++) U[j] = V[j] - W[j];
        return U;
    }
    
    vector operator+(const vector& V, const vector& W)
    {
        int d = (int)V.size();
        vector U(d);
        for (int j = 0; j < d; j++) U[j] = V[j] + W[j];
        return U;
    }
    
    vector operator/(const vector& V, const int& a)
    {
        int d = (int)V.size();
        vector U(d);
        for (int j = 0; j < d; j++) U[j] = V[j]/a;
        return U;
    }
}
