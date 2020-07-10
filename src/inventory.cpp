#include "inventory.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <thread>
#include <chrono>
#include <utility>
#include <vector>
#include <ctime>

#include <curl/curl.h>
#include <jsoncpp/json/json.h>

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

/*This function make requests to steam server in order to get
json file with items which steam user have. It can steam items 
or items from any other game. After successful of this funtion 
.txt file with list of items will be created in folder /out
*/
void inventory::get()
{
    std::vector<std::pair<std::string, float>> data; // string is a name of item, float is a price 

    for(int j = 0; j < 1000; j+=100)
    {
        CURL *curl;
        CURLcode res;
        std::string readBuffer;
        std::string url = "https://steamcommunity.com/market/search/render/?query=&start=" + std::to_string(j) +"&count=1000&norender=1&currency=3&&appid=730";
        curl = curl_easy_init();
        if(curl) 
        {
            readBuffer = "";
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);
        }

        std::system("clear");
        State((j+100)/2500.);
        if(readBuffer.size() < 25)
        {
            std::cout << "\033[31mRequest failed!\033[0m"<< std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        else
        {
            Json::Reader reader;
            Json::Value obj;
            reader.parse(readBuffer, obj);

            for(int i = 0; i < obj["results"].size(); i++)
            {
                float price = std::stof(obj["results"][i]["sale_price_text"].asString().substr(1));
                std::string name = obj["results"][i]["name"].asString();
                if(price > 0.5 && price < 1000/27.5)
                    data.push_back(std::make_pair(name, price));

            }
        }


        /*std::thread t1(&Steam::ParseAndAddToMap, this,  std::ref(data), std::ref(readBuffer));
        t1.join();*/

    }


    if(data.size()> 0)
    {
        std::ofstream file;
        time_t now = time(0);
        tm *ltm = localtime(&now);
        std::string filename = std::to_string(ltm->tm_hour) + ":" 
                            + std::to_string(ltm->tm_min);
        file.open("../out/" +filename +".txt");
        for(auto a: data)
            file << a.first << ";" << a.second << std::endl;
        std::cout << "\033[32mDone!\033[0m"<< std::endl;
    }
    else
        std::cout << "\033[31mAll requests failsed. No data to write!\033[0m"<< std::endl;
}
void steam::State(double per)
{
    int color;
    for(int i = 0; i<=per*100; i++)
    {
        if(per >=0 && per <0.2)
            color = 31;
        else if(per >= 0.2 && per<=0.4)
            color = 33;
        else if(per >= 0.4 && per<=0.6)
            color = 92;
        else if(per >= 0.6 && per<=0.8)
            color = 34;
        else
            color = 35;
        
        std::cout <<"\033["+std::to_string(color)+"m|";
    }
        std::cout <<"\033[0m" << std::setw(107-per*100)<< ""<< std::setprecision(3) << per*100 <<"%\n";

}