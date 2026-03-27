#pragma once // Garante que o arquivo não seja incluído duas vezes
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>



void logError(std::string originWay, std::string logErro) // Da pra colocar mais de um parametro em uma função void
{
    std::string nome;

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

    if (archive_pos != std::string::npos)
    {
        nome = originWay.substr(archive_pos + 1);
    }
    else {
        nome = originWay;
    }

    archive_pos = (nome.find_last_of("."));
    nome = nome.substr(0, archive_pos) + "_errors.log";

    std::ofstream arqLog;
    arqLog.open(nome, std::ios::app);

    if (arqLog.is_open())
    {
        arqLog << "[" << info->tm_mday << "/" //Dia
                            << info->tm_mon + 1 << "/" //Mês
                            << info->tm_year + 1900<< " " // Ano
                            << info->tm_hour << ":" // Hora
                            << info->tm_min << ":" // Minuto
                            << info->tm_sec << "] "; // Segundo
        
        arqLog << "Arquivo: " << originWay << "\n" << std::endl;
        arqLog << "Erro: " << logErro << "\n" << std::endl;
        arqLog.close();
    }
}