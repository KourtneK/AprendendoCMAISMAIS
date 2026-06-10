#include <float.h>
#include <conio.h>
#include <iostream>
#include <minwindef.h>
#include "lspClient.hpp"


struct Snippet
{
    const char* gatilho;
    const char* conteudo;
};

// Snippets
Snippet snippets[] = 
{
    {"main", "int main(int argc, const char** argv[])\n{\n   \n  return0;}"}

};

int totalSnippets = sizeof(snippets) / sizeof(Snippet);

int main(int argc, const char** argv)
{
    HANDLE pipe;
    pipe = CreateNamedPipe("\\\\.\\pipe\\lsp", PIPE_ACCESS_DUPLEX, PIPE_TYPE_BYTE | 
                            PIPE_READMODE_BYTE | PIPE_WAIT, 1, sizeof(lspResponse), sizeof(lspRequest), 0, NULL);

    if (pipe == INVALID_HANDLE_VALUE)
    {
        std::cerr << "Erro ao criar pipe" << std::endl;

        return 1;
    }

    while (true)
    {
        ConnectNamedPipe(pipe, NULL);

        lspRequest request;

        DWORD bytesLidos;
        BOOL ok = ReadFile(pipe, &request, sizeof(lspRequest), &bytesLidos, NULL);

        if (!ok || bytesLidos == 0)
        {
            break;
        }

        lspResponse response;
        response.qntSuggest = 0;

        std::string texto(request.texto);

        for (int i = 0; i < totalSnippets && response.qntSuggest < 10; i++)
        {
            std::string gatilho(snippets[i].gatilho);

            if (gatilho.find(texto) == 0 || texto.find(gatilho) == 0)
            {
                strncpy(response.suggest[response.qntSuggest], snippets[i].conteudo, 255);

                response.suggest[response.qntSuggest][255] = '\0';
                response.qntSuggest++;
            }
        }

        DWORD bytesEscritos;
        WriteFile(pipe, &response, sizeof(lspResponse), &bytesEscritos, NULL);

        DisconnectNamedPipe(pipe);

    }

    CloseHandle(pipe);

    return 0;
}
