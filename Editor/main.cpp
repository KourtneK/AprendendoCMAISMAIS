#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>
#include <float.h>
#include <conio.h>
#include <fstream>
#include <windows.h> 

std::vector<std::string> buffer;

char key;

int main(int argc, char* argv[])
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    size_t terminalWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;

    std::cout << "Largura do terminal: " << terminalWidth << "; " << "(Muda toda vez que voce redimensiona o terminal, sai e entra de novo no editor)" << std::endl;

    std::cout << "Bem vindo ao editor;" << std::endl;

    buffer.push_back("");

    while (true)
    {
        key = _getch();

        if (key == 27)
        {
            system("cls");
            break;
            
        }

        if (key == 8)
        {
            if (!buffer.back().empty())
            {
                buffer.back().pop_back();

                std::cout << "\b \b";

            }

            else if (buffer.back().empty() <= terminalWidth | buffer.size() > 1)
            {
                buffer.pop_back();
                
                std::cout << "\033[A" << std::endl;

                std::cout << "\033[" << buffer.back().length() + 1 << "G";
            
            }

        }

        if (key >= 32 && key <= 126)
        {
            if (buffer.back().length() >= terminalWidth)
            {
               std::cout << '\n';

               buffer.push_back("");
            
            }

            buffer.back() += key;

            std::cout << key;
       
        }
    
    }
    


    return 0;
}
