#pragma once // Garante que o arquivo não seja incluído duas vezes
#include <iostream>
#include <string>
#include <cstdlib> // Necessário para o std::exit()




void checkExit(std::string cmdE) {
    if (cmdE == "exit") {
        std::exit(0);
    }
}