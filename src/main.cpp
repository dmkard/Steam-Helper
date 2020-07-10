#include <iostream>
#include <string>
#include "steam.h"
#include "compare.h"
int main()
{
    while(1)
    {
 
        std::string action;
        std::cout << "\033[32m\n\t\t\t\t    STEAM HELPER\033[0m\n\n";
        std::cout << "################################################################################\n";
        std::cout << "Allowed commands: \n"
                <<"    get       - get a list of currently most popular on Steam Market CS:GO items\n"
                <<"    inventory - show CS:GO inventory price\n"
                <<"    compare   - compate prices of items from two files\n"
                <<"    exit      - exit the program\n"
                <<"Enter action: "; 
        std::cin >> action;
        
        if(action == "get")
        {
            steam::get();
            //TODO: various games to choose

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