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

        float var1, var2;


        std::cout << "digita um numero ";
        std::cin >> var1;
        std::cout << "digita um numero ";
        std::cin >> var2;


        float sum = (var1 + var2) / 2.0f;

        if (sum < 6.0f) {
            std::cout << "media eh baixa " << sum << std::endl;
        }
        else {
            std::cout << "media eh alta " << sum << std::endl;
        }

        std::cout << "digite start para continuar ou exit para sair" << std::endl;
    }
}

int main() {
    std::string cmd = "start";

    do
    {
        start(cmd);
  
        std::cin >> cmd;
        
        exit(cmd);





    } while (cmd != "exit");
    

    return 0;
}