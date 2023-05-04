#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
#include <iomanip>
#include <sstream>
#include<cmath>
#include <fstream>
#include <locale>
#include "curl/curl.h"


using namespace std;
namespace project{
    class Webscraper{
        private:
        string startdate;
        string enddate;
        
        public:
            Webscraper(string startdate_, string enddate_)
            {
                startdate = startdate_;
                enddate = enddate_;
            }
            void getStockData();
            void getIWVData();
        
    };
}

