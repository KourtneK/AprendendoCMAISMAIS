#include <iostream>
#include <fstream>
#include <string>
#include "sair.h"


/*
SINTAXE BASICA DA LIB fstream

std::ofstream: (Output File) Serve para escrever.
std::ifstream: (Input File) Serve para ler.
std::fstream: (File Stream) Ler e escrever, mas exige que você diga o que quer fazer na hora de abrir.


*/

// MEXENDO COM ARQUIVOS COM C++

int main() {
    std::ofstream arquivo("first file.txt"); // Cria um arquivo chamado "first file.txt"
    std::ifstream ler_arquivo; // Define a função de ler arquivo

    if (arquivo.is_open()) // Pergunta se o arquivo pode ser aberto/criado
    {
        arquivo << "arquivo criado"; // Escreve dentro do arquivo
        arquivo.close(); // Fecha o arquivo

        ler_arquivo.open("first file.txt"); // Lê o arquivo
        
    }

    std::string conteudo_arquivo; // Define a função de mostrar o conteudo arquivo
    conteudo_arquivo = "first file.txt"; // Define qual arquivo vai ser mostrado o conteudo

    while (std::getline(ler_arquivo, conteudo_arquivo)) /* Pega a primeira linha do arquivo.
                                                           Chama a função ler arquivo e conteudo arquivo.
                                                           lê o arquivo e mostra o conteudo no terminal*/
    {
        std::cout << "conteudo do arquivo: " << conteudo_arquivo << std::endl; // Chama o conteudo do arquivo
    }

    ler_arquivo.close(); // fecha o arquivo

    return 0;
}