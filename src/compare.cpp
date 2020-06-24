#include "compare.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <thread>
#include <map>
#include <vector>

Compare::Compare(const std::string &file1,const std::string &file2):
    _filename1(file1), _filename2(file2)
{}
void Compare::Run()
{
    std::ifstream fileStream1, fileStream2;
    fileStream1.open("../out/"+_filename1);
    fileStream2.open("../out/"+_filename2);
    if(fileStream1.is_open())
    {
        if(fileStream2.is_open())
        {
            std::map<std::string, float> map1;
            std::map<std::string, float> map2;
            std::thread t1(&Compare::readFile, this,  std::ref(fileStream2), std::ref(map2));
            readFile(fileStream1, map1);
            t1.join();

            std::vector<Item> items;
            for(auto a: map2)
            {
                float change = ((a.second-map1[a.first])/map1[a.first])*100;
                if(change < -13&& a.second > 0.05)
                    items.push_back({a.first, a.second, change});
            }  
            std::sort(items.begin(), items.end(),[](const Item& a, const Item& b )-> bool{return a.change < b.change;});

            std::ofstream file;
            time_t now = time(0);
            tm *ltm = localtime(&now);
            std::string filename = std::to_string(ltm->tm_hour) + ":" 
                                + std::to_string(ltm->tm_min);
            file.open("../out/change/change_" +filename +".txt");
            for(Item a: items)
            {
                std::cout << std::setw(6) << "\033[32m ⇘ " << a.change << " %\033[0m " <<std::setw(5) <<a.price<< " " << a.name << std::endl;
                file << std::setw(6) << "⇘" << a.change << " % " <<std::setw(5) <<a.price<< " " << a.name << std::endl;
            }
            std::cout << "\033[32mComparison is done!\033[0m"<< std::endl;
        }
        else
        {
            std::cout << "File with name\"" << _filename2 << "\" is unavailable.\n";
        }
    }
    else
    {
        std::cout << "File with name \"" << _filename1 << "\" is unavailable.\n";
    }
    
}
void Compare::readFile(std::ifstream& fileStream, std::map<std::string, float>& map)
{
    std::string name, price;
    while(std::getline(fileStream, name, ';'))
    {
        std::getline(fileStream, price);
        map[name] = std::stof(price);
    }
}
