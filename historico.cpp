#include <iostream>
#include <cstdlib>
#include <string>
#include <float.h>
#include <limits>
#include "sair.h"
#include "ctime"
#include "fstream"
#include <math.h>


/*
SINTAXE BASICA DA LIB ctime

time_t: É o tipo de variável que guarda o tempo "bruto" (segundos desde 1970).
tm: É uma struct (estrutura) que quebra esse tempo bruto em dia, mês e ano.
localtime: É a função que faz a conversão do tempo bruto para a estrutura de tempo humana.



*/


// FUNÇÃO DE NOTAS
void notas()
{
    int nota; // Define um inteiro para nota
    nota = 000; // Define a nota como 000
    std::cout << "qual a nota\n"; // Mostra a pergunta
    std::cin >> nota; // Pede a nota


    float nota_convert; // Define o conversor de notas como float
    nota_convert = 10.0; // Define o valor base do conversor como 10.0 (float)

    float sum = nota / nota_convert; // Soma a nota inteira com a nota float ( a soma tambem a eh float)

    std::cout << sum << std::endl; // Exibe a soma






    return;
}

// HISTORICO DE MATERIAS
int main()
{
    std::string materia; // Define materia como texto
    std::cout << "qual materia\n" << std::endl; // pergunta qual a materia
    std::getline(std::cin >> std::ws, materia); // pede o nome da materia e pega a ultima linha não usada do arquivo e coloca a materia

    std::ofstream arquivo(materia + ".txt", std::ios::app); // Define um arquivo para cada materia

    // Cria o arquivo da materia se ele puder ser aberto
    if (arquivo.is_open()) // pergunta se o arquivo pode er aberto/criado
    {
        arquivo << "materia adicionada\n" << std::endl; // Exibe a materia adicionada
        arquivo.close(); // fecha o arquivo


    }





    return 0;
}
