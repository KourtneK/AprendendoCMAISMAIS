#include <iostream>
#include <cstdlib>
#include <string>
#include "sair.h"
#include "errorlog.h"

int main()
{
    int* reserva_de_espaco_de_memoria = new int;
    *reserva_de_espaco_de_memoria = 40;

    std::cout << "valor: " << *reserva_de_espaco_de_memoria << "\n" << std::endl;
    std::cout << "endereco na memoria: " << reserva_de_espaco_de_memoria << "\n" << std::endl;

    delete reserva_de_espaco_de_memoria;
    reserva_de_espaco_de_memoria = nullptr;

    return 0;
}
