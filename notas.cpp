#include <iostream>
#include <cstdlib>
#include <string>
#include <float.h>

int main() {
    system("cls");

    float var = 3.5;
    float var2 = 1.4;

    float sum = (var + var2) / 2.0f;

    if (sum < 6.7) {
        std::cout << "media eh baixa " << sum << std::endl;
    }
    else {
        std::cout << "media eh alta " << sum << std::endl;
    }







    

    std::string entrada;

    while (entrada != "exit")
        std::cin >> entrada;
    return 0;
}