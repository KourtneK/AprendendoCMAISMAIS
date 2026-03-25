#include <iostream>
#include <fstream>
#include <string>
#include "sair.h"


/*
std::ofstream: (Output File) Serve para escrever.
std::ifstream: (Input File) Serve para ler.
std::fstream: (File Stream) Ler e escrever, mas exige que você diga o que quer fazer na hora de abrir.


*/

// MEXENDO COM ARQUIVOS COM C++

int main() {
    std::ofstream nome_arquivo("first file.txt");
    std::ifstream ler_arquivo;

    if (nome_arquivo.is_open())
    {
        nome_arquivo << "arquivo criado";
        nome_arquivo.close();

        ler_arquivo.open("first file.txt");
        
    }

    std::string conteudo_arquivo;
    conteudo_arquivo = "first file.txt";

    while (std::getline(ler_arquivo, conteudo_arquivo))
    {
        std::cout << "conteudo do arquivo: " << conteudo_arquivo << std::endl;
    }

    ler_arquivo.close();









    return 0;
}