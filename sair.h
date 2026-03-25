#pragma once // Garante que o arquivo não seja incluído duas vezes
#include <iostream>
#include <string>
#include <cstdlib> // Necessário para o std::exit()


// cmdE = command exit

// se o comando for igual a "exit" o programa fecha

void checkExit(std::string cmdE) {
    if (cmdE == "exit") {
        std::exit(0);
    }
}