#include <iostream>
#include <cstdlib>
#include <string>
#include <float.h>
#include <limits>
#include <ctime>
#include <fstream>
#include <math.h>
#include "sair.h"
#include "errorlog.h"

/*
SINTAXE BASICA DA LIB ctime

time_t: É o tipo de variável que guarda o tempo "bruto" (segundos desde 1970).
tm: É uma struct (estrutura) que quebra esse tempo bruto em dia, mês e ano.
localtime: É a função que faz a conversão do tempo bruto para a estrutura de tempo humana.

SINTAXE DA LIB string

find_last_of: Para encontrar onde termina a última barra (/ ou \) do endereço.
substr: Para cortar a string e pegar apenas o nome do arquivo.
*/

// FUNÇÃO DE NOTAS
float notas()
{
    int nota; // Define um inteiro para nota
    nota = 0; // Define a nota como 000
    std::cout << "qual a nota\n"; // Mostra a pergunta
    std::cin >> nota; // Pede a nota

    if (nota > 100)
    {
        logError(__FILE__, "omaga, digitaste uma nota maio q 100\n");
    }

    float nota_convert; // Define o conversor de notas como float
    nota_convert = 10.0; // Define o valor base do conversor como 10.0 (float)

    float sum = nota / nota_convert; // Soma a nota inteira com a nota float ( a soma tambem a eh float)

    std::cout << sum << std::endl; // Exibe a soma (float)

    return sum; // return tambem pode retornar parametros, como, inteiro, float, sum, nota, nota_convert
}

// HISTORICO DE MATERIAS
int main()
{
    std::string archive_nome = __FILE__;
    std::string archive_final = __FILE__;

    float media = notas(); // Chama a função notas

    system("cls");

    time_t tempo = std::time(0); // Declara uma variavel da lib ctime chamada tempo e chama a função time(0)

    struct tm* info = std::localtime(&tempo); // Ionforma o tempo usando abstração

    int dia = info->tm_mday;
    int mes = info->tm_mon + 1;
    int ano = info->tm_year + 1900;
    int hora = info->tm_hour;
    int minuto = info->tm_min;
    int segundo = info->tm_sec;
    
    std::string materia; // Define materia como texto
    std::cout << "qual materia\n" << std::endl; // pergunta qual a materia
    std::getline(std::cin >> std::ws, materia); // pede o nome da materia e pega a ultima linha não usada do arquivo e coloca a materia

    std::ofstream arquivo(materia + ".txt", std::ios::app); // Define um arquivo para cada materia

    // Cria o arquivo da materia se ele puder ser aberto
    if (arquivo.is_open()) // pergunta se o arquivo pode er aberto/criado
    {
        arquivo << "materia adicionada" << std::endl; // Exibe a materia adicionada

        // Define a data e horario
        arquivo << "[" << info->tm_mday << "/" //Dia
                        << info->tm_mon + 1 << "/" //Mês
                        << info->tm_year + 1900<< " " // Ano
                        << info->tm_hour << ":" // Hora
                        << info->tm_min << ":" // Minuto
                        << info->tm_sec << "] "; // Segundo

        arquivo << "materia: " << materia << " "; // Define a materia
        system("cls");
        arquivo << "nota: " << media << "\n" << std::endl; // Define a nota
        arquivo.close(); // fecha o arquivo

    }

    return 0;
}