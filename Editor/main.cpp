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

int key;

int cLinha;
int cColuna;

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
            << "(Muda toda vez que 'voce redimensiona o terminal, " 
            << "sai e entra de novo no editor)" << std::endl;
    std::cout << "Cursor: X=" << csbi.dwCursorPosition.X << " Y=" << csbi.dwCursorPosition.Y << std::endl;
    std::cout << "Bem vindo ao editor;" << '\n';

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

    cColuna = buffer.back().length();
    cLinha = buffer.size() - 1;

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

        if (key == 224)
        {
            key = _getch();

            if (key == 72 && csbi.dwCursorPosition.Y > cursorInicialPosY && cLinha > 0) // Seta pra cima
            {
                std::cout << "\033[A";

                cLinha--;
            }

            if (key == 80 && cLinha < (int)buffer.size() - 1) // Seta pra baixo
            {
                std::cout << "\033[B";

                cLinha++;
            }

            if (key == 75 && csbi.dwCursorPosition.X > 0) // Seta pra esquerda
            {
                std::cout << "\033[D";

                cColuna--;
            }

            if (key == 77 && csbi.dwCursorPosition.X < buffer[cLinha].length()) // Seta pra direita
            {
                std::cout << "\033[C";

                cColuna++;
            }

            continue;
        }

        if (key == 8)
        {
            if (!buffer.back().empty() && inEditor)
            {
                buffer.back().pop_back();

                cColuna--;

                std::cout << "\b \b";
            }

            else if (buffer.size() > 1)
            {
                buffer.pop_back();

                std::cout << "\033[1A";
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
            // std::cout << "cLinha=" << cLinha << " buffer.size()=" << buffer.size() << std::endl;

            if (buffer.back().length() >= terminalWidth)
            {
                std::cout << std::endl;

                buffer.push_back("");
            }

            buffer[cLinha].insert(cColuna, 1, (char)key);
            cColuna++;

            std::cout << (char)key;
        }
    }
    

    return 0;
}
