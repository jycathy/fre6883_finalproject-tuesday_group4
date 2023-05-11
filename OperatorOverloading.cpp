#include "OperatorOverloading.h"
#include <cmath>
using namespace std;
namespace project {
    vector<double> operator-(const vector<double>& V, const vector<double>& W)
    {
    int d = (int)V.size();
    vector<double> U(d);
    for (int j = 0; j < d; j++) U[j] = V[j] - W[j];
    return U;
    }
    
    vector<double> operator+(const vector<double>& V, const vector<double>& W)
    {
    int d = (int)V.size();
    vector<double> U(d);
    for (int j = 0; j < d; j++) U[j] = V[j] + W[j];
    return U;
    }
    
    vector<double> operator/(const vector<double>& V, const int& a)
    {
    int d = (int)V.size();
    vector<double> U(d);
    for (int j = 0; j < d; j++) U[j] = V[j] / a;
    return U;
    }
     
}