#pragma once
#include <vector>

using namespace std;
namespace project{
    class GnuPlot
    {
    private:
        vector<double> CAAR1;
        vector<double> CAAR2;
        vector<double> CAAR3;
        int dataSize;
        
    public:
        GnuPlot(const vector<double> &yData1_, const vector<double> &yData2_, const vector<double> &yData3_)
        {
            CAAR1 = CAAR1_;
            CAAR2 = CAAR2_;
            CAAR3 = CAAR3_;
            dataSize = CAAR1_.size();
        }
        ~GnuPlot(){}
        vector<double> GetData1(){return CAAR1;}
        vector<double> GetData2(){return CAAR2;}
        vector<double> GetData3(){return CAAR3;}
        void plotResults() const;
    };
}