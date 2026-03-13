#include <iostream>
#include <cstdlib>
#include <string>
#include <float.h>



void exit(std::string cmdE) {
    if (cmdE == "exit")
    {
        std::exit(0);
    }
    
}

void start(std::string cmdS) {
    if (cmdS == "start") {
        system("cls");

        float var1 = 0;
        float var2 = 0;

        std::cout << "digita um numero ";
        std::cin >> var1;
            
        std::cout << "digita um numero ";
        std::cin >> var2;

        float sum = (var1 + var2) / 2.0f;

        if (sum < 6.7) {
            std::cout << "media eh baixa " << sum << std::endl;
        }
        else {
            std::cout << "media eh alta " << sum << std::endl;
        }

        std::cout << "digite start para continuar ou exit para sair" << std::endl;
    }
}

int main() {
    std::string cmdE = "start";

    do {
        if (cmdE == "start")
        {
            start(cmdE);
        }
        std::cin >> cmdE;

        exit(cmdE);

    } while (cmdE == "start");

    return 0;
}