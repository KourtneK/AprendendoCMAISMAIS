#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>
#include <float.h>
#include <conio.h>
#include <fstream>
#include <windows.h>


char keyState;

int main(int argc, char* argv[])
{
    system("cls");

    std::vector<std::string> buffer;
    
    buffer.push_back("");

    char key;

    while (true)
    {
        key = _getch();

        if (key == 27)
        {
            break;
            
        }

        if (key == 8)
        {
            if (!buffer.back().empty())
            {
                buffer.back().pop_back();

                std::cout << "\b \b";
            
            }
        }

        if (key >= 32 && key <= 126)
        {
            buffer.back() += key;

            std::cout << key;
       
        }
    
    }
    


    return 0;
}