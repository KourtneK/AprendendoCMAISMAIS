#include "dyad.h"
#include <iostream>

int main()
{
    system("cls");

    int firstInt,
        secondInt;

    double firstDouble,
            secondDouble;

    char firstChar,
        secondChar;

    Dyad<int> dyadInt(1, 2);
    Dyad<double> dyadDouble(1.5, 2.5);
    Dyad<char> dyadChar('A', 'B');

    std::cout << "First int: " << dyadInt.getFirst()
                << "\nSecond int: " << dyadInt.getSecond() << std::endl;

    dyadInt.swapVlaues();
    dyadInt.get2Values(firstInt, secondInt);

    std::cout << "\nFirst double after swap: " << firstInt
                << "\nSecond double after swap:" << secondInt
                << "\nFirst char: " << dyadDouble.getFirst()
                << "\nSecond char: " << dyadDouble.getSecond() << std::endl;

    dyadDouble.swapVlaues();
    dyadDouble.get2Values(firstDouble, secondDouble);

    
    std::cout << "\nFirst double after swap: " << firstChar
                << "\nSecond double after swap:" << secondChar
                << "\nFirst char: " << dyadChar.getFirst()
                << "\nSecond char: " << dyadChar.getSecond() << std::endl;

    dyadChar.swapVlaues();
    dyadChar.get2Values(firstChar, secondChar);


    return 0;
}