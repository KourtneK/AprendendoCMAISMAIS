#pragma once // Garante que o arquivo não seja incluído duas vezes
#include <iostream>
#include <string>
#include <cstdlib> // Necessário para o std::exit()
#include <fstream>
#include <ctime>




// cmdE = command exit

// se o comando for igual a "exit" o programa fecha

void checkExit(std::string cmdE)
{
    if (cmdE == "exit") {
        std::exit(0);
    }
}

void logError(std::string originWay, std::string logErro) // Da pra colocar mais de um parametro em uma função void
{
    time_t tempo = std::time(0); // Declara uma variavel da lib ctime chamada tempo e chama a função time(0)

    struct tm* info = std::localtime(&tempo); // Ionforma o tempo usando abstração

    int dia = info->tm_mday;
    int mes = info->tm_mon + 1;
    int ano = info->tm_year + 1900;
    int hora = info->tm_hour;
    int minuto = info->tm_min;
    int segundo = info->tm_sec;

    size_t archive_pos;
    

    archive_pos = (originWay.find_last_of("\\/"));
    logErro = originWay.substr(originWay.find_last_of(".\\"));
    logErro = originWay + "_errors.log";

    if (archive_pos != std::string::npos)
    {
        originWay = originWay.substr(archive_pos + 1);
    }

    std::ofstream arqLog;
    arqLog.open(logErro, std::ios::app);
    std::cout << std::ws, arqLog;

    if (arqLog.is_open())
    {
        arqLog << "[" << info->tm_mday << "/" //Dia
                            << info->tm_mon + 1 << "/" //Mês
                            << info->tm_year + 1900<< " " // Ano
                            << info->tm_hour << ":" // Hora
                            << info->tm_min << ":" // Minuto
                            << info->tm_sec << "] "; // Segundo
        
        arqLog << "Arquivo: " << logErro << " ";
        arqLog << "Erro: " << originWay << "\n" << std::endl;
        arqLog.close();
    }
}