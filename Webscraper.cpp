#include <iostream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <locale>
#include <map>
#include "Grouping.h"
#include "Webscraper.h"

using namespace std;

namespace project{
	StockGroups groups;
	
	int write_data(void* ptr, int size, int nmemb, FILE* stream)
	{
		size_t written;
		written = fwrite(ptr, size, nmemb, stream);
		return written;
	}
	struct MemoryStruct {
		char* memory;
		size_t size;
	};
	void* myrealloc(void* ptr, size_t size)
	{
		if (ptr)
			return realloc(ptr, size);
		else
			return malloc(size);
	}
	int write_data2(void* ptr, size_t size, size_t nmemb, void* data)
	{
		size_t realsize = size * nmemb;
		struct MemoryStruct* mem = (struct MemoryStruct*)data;
		mem->memory = (char*)myrealloc(mem->memory, mem->size + realsize + 1);
		if (mem->memory) {
			memcpy(&(mem->memory[mem->size]), ptr, realsize);
			mem->size += realsize;
			mem->memory[mem->size] = 0;
		}
		return realsize;
	}
	
	
	//////////////////////////////////////////////////////////////////////// 
	map<string,string> Webscraper::GetDate(map<string,string> &Date) //
	// convert the announcement from the format of '21-Nov-2022' to '2022-11-21'
	// return a map, the key is the ticker and the value is the converted announcement date
	{
		map<string,string> month;
		month["JAN"]="01";
	    month["FEB"]="02";
	    month["MAR"]="03";
	    month["APR"]="04";
	    month["MAY"]="05";
	    month["JUN"]="06";
	    month["JUL"]="07";
	    month["AUG"]="08";
	    month["SEP"]="09";
	    month["OCT"]="10";
	    month["NOV"]="11";
	    month["DEC"]="12";
	    
	    ifstream fin;
	    fin.open("Russell3000EarningsAnnouncements.csv");
	    string line, year, day, date, symbol, ini_date;
	    getline(fin,line); //skip the first line
	    
	    while (getline(fin,line))
	    {
	    	symbol = line.substr(0,line.find_first_of(","));
	    	line.erase(0,line.find_first_of(",") + 1);
	    	ini_date = line.substr(0,line.find_first_of(","));
	    	day = ini_date.substr(0,2);
	    	year = ini_date.substr(7);
	    	string month_str = ini_date.substr(3, 3);
	        for (int i = 0; i < 3; i++) //make sure all the letters are capital
	        {
	            month_str[i] = toupper(month_str[i]);
	        }
	    	date = year + "-" + month[month_str] + "-" + day;
	    	Date[symbol] = date;
	    }
	    fin.close();
	    return Date;
	}
	
	
	std::vector<string> Webscraper::GetTradingDays() //trading dates
	{
		ifstream fin;
	    fin.open("Trading_dates.csv");
	    vector<string> trading_dates;
	    string line;
	
	    while (getline(fin, line))
	    {
	        trading_dates.push_back(line);
	    }
	    fin.close();
	    return trading_dates;
	}
	
	// N days before the announcement day
	string Webscraper::GetStartDate(map<string,string> &Date, string &symbol, vector<string> &trading_dates, int N)
	// given the map with tickers as keys and converted announcement dates as values, the ticker of the target stock, vector of all trading dates, N
	// return the startDate of the target stock, which is N days before the announcement date
	{
	    auto it = find(trading_dates.begin(), trading_dates.end(), Date[symbol]);
	    if (it == trading_dates.end()) 
	    {
	        return "";
	    }
	    int index = distance(trading_dates.begin(), it);  // the index of the announcement date in the trading dates vector
	    int new_index = index - N;  // the index of the startDate in the trading dates vector
	    if (new_index < 0 || new_index >= trading_dates.size()) 
	    {
	        return "";
	    }
	    return trading_dates[new_index];  // return the startDate
	}
	
	//N days after the announcement day
	string Webscraper::GetEndDate(map<string,string> &Date, string &symbol, vector<string> &trading_dates, int N)
	// given the map with tickers as keys and converted announcement dates as values, the ticker of the target stock, vector of all trading dates, N
	// return the endDate of the target stock, which is N days after the announcement date
	{
	    auto it = find(trading_dates.begin(), trading_dates.end(), Date[symbol]);
	    if (it == trading_dates.end()) 
	    {
	        return "";
	    }
	    int index = distance(trading_dates.begin(), it);  // the index of the announcement date in the trading dates vector
	    int new_index = index + N;  // the index of the endDate in the trading dates vector
	    if (new_index < 0 || new_index >= trading_dates.size()) 
	    {
	        return "";
	    }
	    return trading_dates[new_index];  // return the endDate
	}
	
	
	////////////////////////////////////////////////////////////////////////
	void Webscraper::getStockData(int i) 
	{
		groups.groupStocksBySurprisePercentage("Russell3000EarningsAnnouncements.csv");  // call the function to split the group
	
	    map<string, string> Date;
	    vector<string> trading_dates;
	    
	    Date = GetDate(Date);
	    trading_dates = GetTradingDays();  // all the trading dates
		
		// file pointer to create file that store the data  
		FILE* fp;
		char resultfilename[FILENAME_MAX];
	
		// declaration of an object CURL 
		CURL* handle;
	
		CURLcode result;
	
		// set up the program environment that libcurl needs 
		curl_global_init(CURL_GLOBAL_ALL);
	
		// curl_easy_init() returns a CURL easy handle 
		handle = curl_easy_init();
	
		// if everything's all right with the easy handle... 
		if (handle)
		{
			string url_common = "https://eodhistoricaldata.com/api/eod/";
			string api_token = "644dd3c5307e07.87085785";  // You just replace this API token with yours
			
			this->clearGroupStockMap();  // each time reset N and scrap data, clear group stockMap
			
		
			cout << "Fetching group " << i << " ..." << endl;
			vector<string> currentGroup = groups.getGroup(i);  // get the vector of tickers in this group
			string group_name;
			map<string, Stock_info*> *pMap;  //initiate the pointer pointing to the subgroup stockMap
			
			// set the group_name and the pointer
			if (i == 1)
			{	
			
				group_name = "Beat";
				pMap = &BeatStockMap;
			}
			if (i == 2)
			{
				
				group_name = "Meet";
				pMap = &MeetStockMap;
			}
			if (i == 3)
			{
				
				group_name = "Miss";
				pMap = &MissStockMap;
			}

			std::vector<std::vector<string>> matrix;
			std::vector<string> row;
			for (const string& symbol : currentGroup) {
				string non_const_symbol = symbol;
	    		string startdate = GetStartDate(Date, non_const_symbol, trading_dates, N); //starting date for each stock
	    		string enddate = GetEndDate(Date, non_const_symbol, trading_dates, N);   //ending date for each stock

	    		auto it = StockMap.find(symbol);  // locate the stock in the stockMap
	    		if(it == StockMap.end()) {cout<<"stock not found in stockMap"<<endl;}
	    		
	    		// set the startDate, endDate, and group_name
	    		StockMap[symbol]->setStartDate(startdate);
	    		StockMap[symbol]->setEndDate(enddate);
	    		StockMap[symbol]->setGroup(group_name);
	
				struct MemoryStruct data;
				data.memory = NULL;
				data.size = 0;
				
	
				string url_request = url_common + non_const_symbol + ".US?" + "from=" + startdate + "&to=" + enddate + "&api_token=" + api_token + "&period=d";
				curl_easy_setopt(handle, CURLOPT_URL, url_request.c_str());
	
				//adding a user agent
				curl_easy_setopt(handle, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:74.0) Gecko/20100101 Firefox/74.0");
				curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0);
				curl_easy_setopt(handle, CURLOPT_SSL_VERIFYHOST, 0);
				
	
				curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data2);
				curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void*)&data);
	
				// perform, then store the expected code in result
				result = curl_easy_perform(handle);
	
				if (result != CURLE_OK)
				{
					// if errors have occured, tell us what is wrong with result
					fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));
					return;
				}
				stringstream sData;
				sData.str(data.memory);
				string sValue, sDate;
				double dValue = 0.0;
				vector<double> price;
				
				string line;
				row.push_back(symbol);
				
				while (getline(sData, line)) {
					size_t found = line.find('-');
	    			if (found != std::string::npos)
	    			{
	    			
	    			sDate = line.substr(0, line.find_first_of(','));
	    			line.erase(line.find_last_of(','));
	    			sValue = line.substr(line.find_last_of(',') + 1);
	    			row.push_back(sValue);
	    			dValue = std::stod(sValue);
	    			price.push_back(dValue);  // set the price
	    			}
	    		}
	    		matrix.push_back(row); 
	    		row.clear();
	    		
	    		if(StockMap.find(symbol)==StockMap.end()){ cout<<"stock not found in stockMap!"<<endl;}
	    		
	    		if( price.size()== 2*N+1 )   // avoid segmentation fault
	    		{
	    			StockMap[symbol]->setPrice(price);
		    		StockMap[symbol]->calDailyReturn(); // always calculate daily return before calculating cumulative return
		    		StockMap[symbol]->calCumulativeReturn(); //calculate cumulative return once get price date
		    		StockMap[symbol]->calAbnormalReturn(iwv);
		    		//StockMap[symbol]->printInfo(); // for test use
		    		(*pMap)[symbol] = StockMap[symbol];  // populate the stock into the subgroup
	    		}

			}
			
		}
		else
		{
			fprintf(stderr, "Curl init failed!\n");
			return ;
		}
		// cleanup since you've used curl_easy_init  
		curl_easy_cleanup(handle);
	
		// release resources acquired by curl_global_init() 
		curl_global_cleanup();
	}
	
	
	
	
	void Webscraper::getIWVData(string startdate, string enddate) 
	{
	
		// file pointer to create file that store the data  
		FILE* fp;
	
		const char resultfilename[FILENAME_MAX] = "IWV.txt";
	
		// declaration of an object CURL 
		CURL* handle;
	
		CURLcode result;
	
		// set up the program environment that libcurl needs 
		curl_global_init(CURL_GLOBAL_ALL);
	
		// curl_easy_init() returns a CURL easy handle 
		handle = curl_easy_init();
	
		// if everything's all right with the easy handle... 
		if (handle)
		{
			string url_common = "https://eodhistoricaldata.com/api/eod/";
			string api_token = "644dd3c5307e07.87085785"; 
			
			iwv.clearData(); // clear date_list and price before write
			vector<string> output_dates;
			vector<double> output_prices;
			
			struct MemoryStruct data;
			data.memory = NULL;
			data.size = 0;
	
			string symbol = "IWV";
			string url_request = url_common + symbol + ".US?" + "from=" + startdate + "&to=" + enddate + "&api_token=" + api_token + "&period=d";
			curl_easy_setopt(handle, CURLOPT_URL, url_request.c_str());
	
			//adding a user agent
			curl_easy_setopt(handle, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:74.0) Gecko/20100101 Firefox/74.0");
			curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0);
			curl_easy_setopt(handle, CURLOPT_SSL_VERIFYHOST, 0);
			fp = fopen(resultfilename, "ab");
			fprintf(fp, "%s\n", symbol.c_str());
			curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data);
			curl_easy_setopt(handle, CURLOPT_WRITEDATA, fp);
			result = curl_easy_perform(handle);
			fprintf(fp, "%c", '\n');
			fclose(fp);
			
			curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data2);
			curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void*)&data);
				// perform, then store the expected code in result
				result = curl_easy_perform(handle);
	
				if (result != CURLE_OK)
				{
					// if errors have occured, tell us what is wrong with result
					fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));
					return;
				}
				
				stringstream sData;
				sData.str(data.memory);
				string sValue, sDate;
				double dValue = 0;
				double sum = 0;
				string line;
				//cout << symbol << endl;
				while (getline(sData, line)) {
					size_t found = line.find('-');
					if (found != std::string::npos)
					{
						//cout << line << endl;
						sDate = line.substr(0, line.find_first_of(','));
						line.erase(line.find_last_of(','));
						sValue = line.substr(line.find_last_of(',') + 1);
						dValue = strtod(sValue.c_str(), NULL);
						//cout << sDate << " " << std::fixed << ::setprecision(6) << dValue << endl;
						output_dates.push_back(sDate);
						output_prices.push_back(dValue);
					}	
				}
				
				iwv.set_all_dates(output_dates);
				iwv.set_Price(output_prices);
				cout<<"IWV data loaded!"<<endl;
				//iwv.printTest();
				
				free(data.memory);
				data.size = 0;
			
	
		}
		else
		{
			fprintf(stderr, "Curl init failed!\n");
			return ;
		}
	
		// cleanup since you've used curl_easy_init  
		curl_easy_cleanup(handle);
	
		// release resources acquired by curl_global_init() 
		curl_global_cleanup();
	
	}
	
	void Webscraper::createStockMap(string filename)
	    // create whole stockMap from Announcement csv file
	{
		ifstream ifile;
		ifile.open(filename, ios::in);
		if (!ifile.is_open())
			cout << "Error file not opened" << endl;
		//else
			//cout << "open" << endl;
		string line, word;
		vector<string> row;
		ifile.ignore(10000, '\n');
		while (!ifile.eof())
		{
			row.clear();

			getline(ifile, line);
			if (!line.empty()) {

				stringstream s(line);

				while (getline(s, word, ','))
				{
					row.push_back(word);
				}
				
				Stock_info* st = new Stock_info(row[0], row[1], row[2], row[3], row[4], row[5], row[6]);  // create object
				StockMap.insert(pair<string, Stock_info*>(row[0], st));  // populate the object into stockMap
			}

		}
		ifile.close();
		cout<<"stockMap created!"<<endl;
	}
	
	
	void Webscraper::clearGroupStockMap()
	// initiate group stock maps
	{
		for (auto i : BeatStockMap)
		{
			delete i.second;
			i.second = NULL;
		}
		for (auto i : MeetStockMap)
		{
			delete i.second;
			i.second = NULL;
		}
		for (auto i : MissStockMap)
		{
			delete i.second;
			i.second = NULL;
		}
		BeatStockMap.clear();
		MeetStockMap.clear();
		MissStockMap.clear();
	}

}

/*
int main()
{
    project::Webscraper Scraper(5);
    Scraper.createStockMap("Russell3000EarningsAnnouncements.csv");
    Scraper.getIWVData("2022-01-03","2023-05-04");
    Scraper.getStockData();
    
    project::Matrix beatARmatrix = createStockARmtx(Scraper.GetBeatStockMap());
    
    int M=80; // randomly pick 80 stocks from beat group
    project::Matrix selectedBeatARmatrix = project::genSelectedARmtx(beatARmatrix,M);
    vector<double> beatAAR = project::calculateAAR(selectedBeatARmatrix);
    vector<double> beatCAAR = project::calculateCAAR(beatAAR);
   
    cout<<"beat group AAR"<<endl;
    for(vector<double>::iterator itr=beatAAR.begin(); itr!=beatAAR.end(); itr++)
    {
    	cout<<*itr<<" ";
    }
    cout<<endl;
    cout<<"beat group CAAR"<<endl;
    for(vector<double>::iterator itr=beatCAAR.begin(); itr!=beatCAAR.end(); itr++)
    {
    	cout<<*itr<<" ";
    }
    cout<<endl;
    
    
    /*
    int m = beatARmatrix.size();
    vector<double>::iterator itr;
    for(int i=0; i<m; i++)
    {
        for(itr=beatARmatrix[i].begin(); itr!=beatARmatrix[i].end(); itr++)
        {cout<< *itr << " ";}
        cout<<endl;
    }
    */
    
  
	
// }