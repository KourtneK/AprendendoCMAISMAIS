#include <iostream>
#include <cstdlib>
#include <string>
#include <float.h>
#include <limits>
#include "sair.h"
#include "ctime"
#include "fstream"
#include "errorlog.h"


int main()
{
    int num;
    num = 10;
    
    std::cout << num << "\n" << std::endl;
    std::cout << &num << "\n" << std::endl;

    int* ponteiro;
    ponteiro = &num;
    *ponteiro = 567890;

    std::cout << ponteiro << "\n" << std::endl;
    std::cout << *ponteiro << "\n" << std::endl;

    return 0;
}
