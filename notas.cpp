#include <iostream>
#include <cstdlib>
#include <string>
#include <float.h>

int main() {

    std::string comando;
    comando = "start";

    do {
        if (comando == "start") {
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
    }
        std::cin >> comando;
    } while (comando == "start");
    
    







    

    std::string entrada;

    while (entrada != "exit") {
        std::cin >> entrada;
    }
    return 0;
}