#ifndef LSPCLIENT_HPP
#define LSPCLIENT_HPP

#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <time.h>
#include <float.h>
#include <conio.h>
#include <windows.h>
#include <winscard.h>


// Estrutura para o request texto (256Max)
struct lspRequest
{
    char texto[256];
};

// Estrutura para o response texto (10 Largura) (256Max)
struct lspResponse
{
    char suggest[10][256];

    int qntSuggest; // Quantidade de sugestoes
};

namespace lspClient // Garante que o nome nao seja substituido por outra lib
{
    // Conexao do LSP
    inline HANDLE connect()
    {
        HANDLE pipe = CreateFile("\\\\.\\pipe\\lsp", GENERIC_READ | GENERIC_WRITE, 
                                    0, NULL, OPEN_EXISTING, 0, NULL);

        return pipe;
    }

    // Funcao response LSP (recebe o pipe e referencia para constante string texto)
    inline lspResponse searchSuggest(HANDLE pipe, const std::string& texto)
    {
        lspRequest request;
        lspResponse response;

        response.qntSuggest = 0;

        strncpy(request.texto, texto.c_str(), 255);

        request.texto[255] = '\0';

        DWORD bytesEscritos;
        WriteFile(pipe, &request, sizeof(lspRequest), &bytesEscritos, NULL);

        DWORD bytesLidos;
        ReadFile(pipe, &response, sizeof(lspResponse), &bytesLidos, NULL);

        return response;
    }

    inline void lspDraw(short currentLine, short currentColum, const std::vector<std::string>& tabela)
    {
        if (tabela.empty())
        {
            return;
        }

        short linhaAtual;
        linhaAtual = currentLine + 1;   

        std::string screenRenderer;
        screenRenderer = "\033[" + std::to_string(linhaAtual) + ";" + std::to_string(currentColum) + "+------------------------------+";

        for (size_t index = 0; index < tabela.size(); index++)
        {
            short linhaAtual

            screenRenderer = screenRenderer + ("| " + tabela[index]);

            int entrySpaces;
            entrySpaces = 28 - tabela[index].length();

            for (int j = 0; j < entrySpaces; j++)
            {
                screenRenderer = screenRenderer + " ";
            }

            screenRenderer = screenRenderer + "| ";
        }

        screenRenderer =  screenRenderer + "\033[B\r+------------------------------+\033[u";

        std::cout << screenRenderer << std::flush;
    }

    inline void exibirSugestoes(const lspResponse& response)
    {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        SHORT coordX;
        SHORT coordY;
        coordX = csbi.dwCursorPosition.X;
        coordY = csbi.dwCursorPosition.Y;
        size_t terminalWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;


        if (response.qntSuggest == 0)
        {
            return;
        }

        std::vector<std::string> tabela;

        for (int i = 0; i < response.qntSuggest; i++)
        {
            std::string sensor(response.suggest[i]);

            if (sensor.length()> 28)
            {
                sensor = sensor.substr(0, 28);
            }

            tabela.push_back(sensor);
        }

        lspDraw(coordY, coordX, tabela);
    }

    inline void limparSugestoes(int qntSuggest)
    {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        SHORT coordX;
        SHORT coordY;
        coordX = csbi.dwCursorPosition.X;
        coordY = csbi.dwCursorPosition.Y;
        size_t terminalWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;

        for (int i = 0; i < qntSuggest + 2; i++;)
        {
            short linhaAtual;
            linhaAtual = coordY + 1 + i;

            std::cout << "\033[" + std::to_string(linhaAtual) + ";" + std::to_string(coordX) + "H\033[K";
        }

        std::cout << std::flush;
    }
}
#endif
