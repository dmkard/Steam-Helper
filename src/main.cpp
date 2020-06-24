#include <iostream>
#include <string>
#include "steam.h"
#include "compare.h"
int main()
{
    while(1)
    {
 
        std::string action;
        std::cout << "Allowed actions: \n"
                <<"\tcreate - ito read prices from steam and write it into file (30 minutes)\n"
                <<"\tcompare - to compate prices from two files, names of which will be asked later\n"
                <<"\texit - to exit the program\n"
                <<"Enter action: "; 
        std::cin >> action;
        
        if(action == "create")
        {
            Steam steam;
            steam.Create();
        }
        else if(action == "compare")
        {
            std::system("clear");
            std::cout << "Print names of two files, which you would like to use.\n"
                        <<"Program will automaticaly find older one.\n"
                        <<"List of available files: \n";
            std::system("ls --color ../out");
            std::cout << "Print filenames here: ";
            std::string file1, file2;
            std::cin >> file1 >> file2;

            Compare compare(file1, file2);
        }
        else if(action == "exit")
            break;
        else
        {
            std::cout << "\033[31mInvalid command. Try one more time.\033[0m\n";
        }
    } 
}