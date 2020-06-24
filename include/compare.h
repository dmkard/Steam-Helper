#include <string>
#include <map>
#include <vector>

struct Item
{
    std::string name;
    float price;
    float change;
};

class Compare
{
public:
    Compare(const std::string &file1,const std::string &file2);
    void Run();
private:
    void readFile(std::ifstream& fileStream, std::map<std::string, float>& map);
    std::string _filename1;
    std::string _filename2;
};