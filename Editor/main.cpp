#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>
#include <float.h>
#include <conio.h>
#include <fstream>


char keyState;

int main(int argc, char* argv[])
{
    system("cls");

    std::cout << "bem vindo ao editor" << std::endl;

    std::vector<std::string> buffer;

    buffer.push_back("");

    while (true)
    {
        keyState = _getch();

        if (keyState == 27 )
        {
            system("cls");

            break;

        }

        if (keyState == 8)
        {
            if (!buffer.back().empty())
            {
                buffer.back().pop_back();

                std::cout << "\b \b";

            }

            else if (buffer.size() > 1)
                {
                    buffer.pop_back();

                    std::cout << "\033[A";

                    int largura = buffer.back().length();

                    std::cout << "\033[" << (largura + 1) << "G";
                
                }

        }
        
        if (keyState == 32)
        {
            if (!buffer.back().empty())
            {
                buffer.back().pop_back();

                std::cout << " ";                
            
            }


        }
        
        if (keyState >= 97 && keyState <= 122)
        {
            buffer.back() += keyState;
            
            std::cout << keyState;
        }

    }

    std::ofstream arquivo("texto.txt");

    if (arquivo.is_open()) {
        for (const std::string& linha : buffer) {
            arquivo << linha << "\n";
        }
        arquivo.close();
    }
    


    return 0;
}