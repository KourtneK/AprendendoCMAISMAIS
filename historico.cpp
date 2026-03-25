#include <iostream>
#include <cstdlib>
#include <string>
#include <float.h>
#include <limits>
#include "sair.h"
#include "ctime"
#include "fstream"


/*
SINTAXE BASICA DA LIB ctime

time_t: É o tipo de variável que guarda o tempo "bruto" (segundos desde 1970).
tm: É uma struct (estrutura) que quebra esse tempo bruto em dia, mês e ano.
localtime: É a função que faz a conversão do tempo bruto para a estrutura de tempo humana.



*/


// FUNÇÃO DE NOTAS
void notas()
{
    int nota;
    nota = 0, 100;

    float nota2;
    nota2 = 0.0, 10.0;




    return;
}











// HISTORICO DE MATERIAS?
int main()
{
    std::string materia;
    std::cout << "qual materia: " << std::endl;
    std::getline(std::cin >> std::ws, materia);

    std::ofstream arquivo(materia + ".txt", std::ios::app);

    if (arquivo.is_open())
    {
        arquivo << "materia adicionada\n" << std::endl;
        arquivo.close();


    }





    return 0;
}
