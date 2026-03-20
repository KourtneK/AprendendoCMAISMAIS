#include <iostream>
#include <cstdlib>
#include <string>
#include <float.h>

/*
VARIAVEIS E STRINGS USADAS

cmdS = command start
cmdE = command exit
cmd = command
var = variavel
*/


/*
FUNÇÕES

exit = funcao que pede o comando de saida
start = funcao que inicia o programa
*/


/*
SINTAXE

std = chama um operador
:: = atua como separador para funcionalidades
cout = inserir uma diticação no programa
<</>> = apontam para o operador da função
void = função que retorna "vazio"?
int = numero inteiro, usado na funçaõ, significa que a função retorna um inteiro, mas como, se as variaveis são float?
cin = exibe algo no programa
*/






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
