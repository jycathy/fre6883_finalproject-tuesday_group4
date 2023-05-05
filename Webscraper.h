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
            Webscraper(string start_date, string end_date)
            {
                startdate = start_date;
                enddate = end_date;
            }
            void getStockData();
            void getIWVData();
        
    };
}

