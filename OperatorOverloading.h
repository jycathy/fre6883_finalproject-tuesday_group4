#pragma once
#include <vector>
#include <iostream>
using namespace std;
namespace project{
    vector<double> operator-(const vector<double>& V, const vector<double>& W);
    vector<double> operator+(const vector<double>& V, const vector<double>& W);
    vector<double> operator*(const vector<double>& V, const vector<double>& W);
    vector<double> operator/(const vector<double>& V, const int& a);
    vector<double> operator*(const vector<double>& V, const int& a);
    vector<double> operator*(const int& a, const vector<double>& V);
}