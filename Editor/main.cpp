#include <cstdlib>
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
#include <winscard.h>
#include "autopairs.hpp"
#include "lspClient.hpp"


std::vector<std::string> buffer;

int key;

int cLinha;
int cColuna;

void attSuggest(HANDLE pipe, lspResponse ultimaResposta)
{
    lspClient::limparSugestoes(ultimaResposta.qntSuggest);
    ultimaResposta.qntSuggest = 0;

    int i;
    i = cColuna;

    while (i > 0 && (isalnum(buffer[cLinha][i]) || buffer[cLinha][i - 1] == '_'))
    {
        i--;
    }

    std::string cWord;
    cWord = buffer[cLinha].substr(i,  cColuna -i);

    if (cWord.empty())
    {
        return;
    }

    lspResponse response;
    response = lspClient::searchSuggest(pipe, cWord);

    if (response.qntSuggest > 0)
    {
        lspClient::exibirSugestoes(response);

        ultimaResposta = response;
    }
}

int main(int argc, char* argv[])
{
    system("cls");

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
    std::cout << "aperte 'esc' para salvar e sair" << std::endl;
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

    cColuna = buffer.back().length();
    cLinha = buffer.size() - 1;

    std::cout << "\033[A";
    std::cout << "\033[" << (cColuna + 1) << "G" << std::flush;

    STARTUPINFO si = { sizeof(si) };
    PROCESS_INFORMATION pi;
    CreateProcess("lspServer.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
    Sleep(100); // espera o servidor iniciar
    HANDLE lspPipe = lspClient::connect();

    lspResponse ultimaResposta;
    ultimaResposta.qntSuggest = 0;

    while (true)
    {
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        bool inEditor = csbi.dwCursorPosition.Y > cursorInicialPosY || 
            (csbi.dwCursorPosition.Y == cursorInicialPosY && csbi.dwCursorPosition.X > cursorInicialPosX);


        key = _getch();
        
        if (key == 27)
        {
            lspClient::limparSugestoes(ultimaResposta.qntSuggest);
            lspClient::disconnect(lspPipe);

            TerminateProcess(pi.hProcess, 0); 
            CloseHandle(pi.hProcess);
            CloseHandle(pi.hThread);

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

                if (cColuna > (int)buffer[cLinha].length())
                {
                    cColuna = buffer[cLinha].length();
                }

                std::cout << "\033[" << (cColuna + 1) << "G";

            }

            if (key == 80 && cLinha < (int)buffer.size() - 1) // Seta pra baixo
            {
                std::cout << "\033[B";

                cLinha++;

                if (cColuna > (int)buffer[cLinha].length())
                {
                    cColuna = buffer[cLinha].length();
                }

                std::cout << "\033[" << (cColuna + 1) << "G";

            }

            if (key == 75 && cColuna > 0) // Seta pra esquerda
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
            if (cColuna > 0 && inEditor)
            {
                buffer[cLinha].erase(cColuna - 1, 1);

                cColuna--;

                std::cout << '\b';

                std::string restoTexto = buffer[cLinha].substr(cColuna);

                std::cout << "\033[K" << restoTexto;

                if (!restoTexto.empty())
                {
                    std::cout << "\033[" << restoTexto.length() << 'D';
                }

                std::cout << std::flush;
                
                }

            else if (buffer.size() > 1 && cLinha > 0)
            {
                std::string cTextLine = buffer[cLinha];

                buffer.erase(buffer.begin() + cLinha);

                cLinha--;

                cColuna = buffer[cLinha].length();
                buffer[cLinha] += cTextLine;

                std::cout << "\033[1A";
                std::cout << "\r\033[K" << buffer[cLinha];
                std::cout << "\n\033[K\033[1A";
                std::cout << "\033[" << cColuna + 1 << "G";
            }
        }

        if (key == 13)
        {
            std::string restoTexto;
            restoTexto = buffer[cLinha].substr(cColuna);

            buffer[cLinha] = buffer[cLinha].substr(0, cColuna);
            buffer.insert(buffer.begin() + cLinha + 1, restoTexto);

            std::cout << "\033[K\n\033[L" << restoTexto << '\r' << std::flush;

            cLinha++;

            cColuna = 0;
        }

        if (key >= 32 && key <= 126)
        {
            // std::cout << "cLinha=" << cLinha << " buffer.size()=" << buffer.size() << std::endl;

            lspResponse response = lspClient::searchSuggest(lspPipe, buffer[cLinha].substr(0, cColuna));

            lspClient::exibirSugestoes(response);
            ultimaResposta = response;

            if (buffer[cLinha].length() >= terminalWidth)
            {
                std::cout << std::endl;

                buffer.insert(buffer.begin() + cLinha + 1, "");

                cLinha++;

                cColuna = 0;

                buffer.push_back("");
            }

            char fechamentoChar;
            fechamentoChar = AutoPairs::get_closing_pair((char)key);

            if (fechamentoChar != '\0')
            {
                buffer[cLinha].insert(cColuna, 1, (char)key);
                buffer[cLinha].insert(cColuna + 1, 1, fechamentoChar);

                std::string restoTexto;
                restoTexto = buffer[cLinha].substr(cColuna);

                cColuna++;

                std::cout << "\033[K" << restoTexto;

                int voltar;
                voltar = restoTexto.length() - 1;

                if (voltar > 0)
                {
                    std::cout << "\033[" << voltar << 'D';
                }

                std::cout << std::flush;
            }
            else
            {
                buffer[cLinha].insert(cColuna, 1, (char)key);

                std::string restoTexto;
                restoTexto = buffer[cLinha].substr(cColuna);

                cColuna++;

                std::cout << "\033[K" << restoTexto;

                int voltar = restoTexto.length() - 1;

                if (voltar > 0)
                {
                    std::cout << "\033[" << voltar << 'D';
                }

                std::cout << std::flush;
            }
        }
    }
    

    return 0;
}
