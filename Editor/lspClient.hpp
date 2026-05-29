#ifndef LSPCLIENT_HPP
#define LSPCLIENT_HPP

#include <cstdlib>
#include <iostream>
#include <string>
#include <time.h>
#include <float.h>
#include <conio.h>
#include <windows.h>


struct lspRequest
{
    char texto[256];
};

struct lspResponse
{
    char suggest[10][256];

    int qntSuggest;
};

namespace lspClient
{
    inline HANDLE connect()
    {
        HANDLE pipe = CreateFile("\\\\.\\pipe\\lsp", GENERIC_READ | GENERIC_WRITE, 
                                    0, NULL, OPEN_EXISTING, 0, NULL);

        return pipe;
    }

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

    inline void exibirSugestoes(const lspResponse& response)
    {
        if (response.qntSuggest == 0)
        {
            return;
        }

        std::cout << "\033[s";
        std::cout << "\033[B";
        std::cout << "\r";

        std::cout << "+";

        for (int i = 0; i < 30; i++)
        {
            std::cout << "-";
        }

        std::cout << "+\n\r";

        for (int i = 0; i < response.qntSuggest; i++)
        {
            std::string s(response.suggest[i]);

            if (s.length() > 28)
            {
                s = s.substr(0, 28);
            }

            std::cout << "| " << s;

            for (int j = s.length(); j < 28; j++)
            {
                std::cout << " ";
            }

            std::cout << " |\n\r";
        }

        std::cout << "+";

        for (int i = 0; i < 30; i++)
        {
            std::cout << "-";
        }

        std::cout << "+";

        std::cout << "\033[u";

        std::cout << std::flush;
    }

    inline void limparSugestoes(int qntSuggest)
    {
        if (qntSuggest == 0)
        {
            return;
        }

        std::cout << "\033[s";

        std::cout << "\033[B\r";

        for (int i = 0; i < qntSuggest + 2; i++)
        {
            std::cout << "\033[K\n\r";
        }

        std::cout << "\033[u" << std::flush;
    }

    inline void disconnect(HANDLE pipe)
    {
        CloseHandle(pipe);
    }
}

#endif
