#include <iostream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <iomanip>
#include <sstream>
#include <locale>
#include "Grouping.h"
#include "curl/curl.h"
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

void Webscraper::getStockData()
{
	groups.groupStocksBySurprisePercentage("Russell3000EarningsAnnouncements.csv");
	
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
		for (int i = 1; i <= 3; i++){
		cout << "Size of group " << i << ": " << groups.getGroup(i).size() << endl;
		vector<string> currentGroup = groups.getGroup(i);
		if (i == 1) {strcpy(resultfilename, "beatEstimateGroup.txt");}
		if (i == 2) {strcpy(resultfilename, "meetEstimateGroup.txt");}
		if (i == 3) {strcpy(resultfilename, "missEstimateGroup.txt");}
		for (const string& symbol : currentGroup) {
            cout << "Current symbol: " << symbol << endl;
			
			struct MemoryStruct data;
			data.memory = NULL;
			data.size = 0;

			
			cout << "url_common: " << url_common << endl;
			cout << "symbol: " << symbol << endl;
			cout << "startdate: " << startdate << endl;
			cout << "enddate: " << enddate << endl;
			cout << "api_token: " << api_token << endl;

			
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

			// check for errors 
			if (result != CURLE_OK) {
				fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));
				return;
			}

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
			cout << symbol << endl;
			while (getline(sData, line)) {
				size_t found = line.find('-');
				if (found != std::string::npos)
				{
					cout << line << endl;
					sDate = line.substr(0, line.find_first_of(','));
					line.erase(line.find_last_of(','));
					sValue = line.substr(line.find_first_of(',') + 1);
					dValue = strtod(sValue.c_str(), NULL);
					cout << sDate << " " << std::fixed << ::setprecision(6) << dValue << endl;
				}	
			}
			
			free(data.memory);
			data.size = 0;
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



void Webscraper::getIWVData()
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
			cout << symbol << endl;
			while (getline(sData, line)) {
				size_t found = line.find('-');
				if (found != std::string::npos)
				{
					cout << line << endl;
					sDate = line.substr(0, line.find_first_of(','));
					line.erase(line.find_last_of(','));
					sValue = line.substr(line.find_first_of(',') + 1);
					dValue = strtod(sValue.c_str(), NULL);
					cout << sDate << " " << std::fixed << ::setprecision(6) << dValue << endl;
				}	
			}
			
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

}


int main()
{
	project::Webscraper Scraper("2023-03-01", "2023-03-31");
	Scraper.getStockData();
	
}

