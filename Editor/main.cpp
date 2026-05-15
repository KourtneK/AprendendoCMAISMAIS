#include <iostream>
#include <fstream>
#include <ostream>
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
    SHORT cursorInicialPosX;
    SHORT cursorInicialPosY;
    cursorInicialPosX = csbi.dwCursorPosition.X;
    cursorInicialPosY = csbi.dwCursorPosition.Y;
    size_t terminalWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;

    std::cout << "Largura do terminal: " << terminalWidth << "; " 
            << "(Muda toda vez que voce redimensiona o terminal, " 
            << "sai e entra de novo no editor)" << std::endl;
    std::cout << "Cursor: X=" << csbi.dwCursorPosition.X << " Y=" << csbi.dwCursorPosition.Y << std::endl;
    std::cout << "Bem vindo ao editor;" << '\n' << std::endl;

    if (argc > 1)
        {
            std::ifstream arquivo(argv[1]);

            if (arquivo.is_open())
            {
                std::string linhas;

                while (std::getline(arquivo, linhas))
                {
                    buffer.push_back(linhas);
                }

                arquivo.close();
            }
            else
            {
                buffer.push_back("");
            }
        }
    else
    {
        std::cout << "chame o editor e digite o nome do arquivo" << std::endl;

        return 0;
    }

    for (const std::string& linha : buffer)
    {
        std::cout << linha << '\n';
    }

    while (true)
    {
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        bool inEditor = csbi.dwCursorPosition.Y > cursorInicialPosY || 
            (csbi.dwCursorPosition.Y == cursorInicialPosY && csbi.dwCursorPosition.X > cursorInicialPosX);


        key = _getch();
        
        if (key == 27)
        {
            std::ofstream arquivo(argv[1]);

            if (arquivo.is_open())
            {
                for (const std::string& linhas : buffer)
                {
                    arquivo << linhas << '\n';
                }

                arquivo.close();
            }

            system("cls");
            break;
        }

        if (key == 8)
        {


            if (!buffer.back().empty() && inEditor)
            {
                buffer.back().pop_back();

                std::cout << "\b \b";
            }

            else if (buffer.size() > 1)
            {
                buffer.pop_back();

                std::cout << "\033[A";
                std::cout << "\033[" << buffer.back().length() + 1 << "G";
            }
        }

        if (key == 13)
        {
            std::cout << '\n';

            buffer.push_back("");
        }

        if (key >= 32 && key <= 126)
        {
            if (buffer.back().length() >= terminalWidth)
            {
                std::cout << std::endl;

                buffer.push_back("");
            }

            buffer.back() += key;

            std::cout << key;
        }
    }
    

    return 0;
}
