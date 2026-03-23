#include <iostream>
#include <cstdlib>
#include <string>
#include <float.h>
#include <limits>

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
void = quando usado em unma função, não retorna nada da função, apenas o que ela faz
int = quando usado dentro de uma função, retorna a função
cin = algo que foi digitado é exibido no programa
include = inclui uma biblioteca no programa
# = operador usado para incluir a biblioteca
</> = operadores usados para colocar o nome da biblioteca que se quer incluir


*/






void exit(std::string cmdE) {
    if (cmdE == "exit")
    {
        std::exit(0);
    }
    
}

void start(std::string cmdS) {
    if (cmdS == "start") {
        

        bool erro = true;
        float var1, var2;

        while (erro) {
            system("cls");

            std::cout << "digita um numero: ";
            std::cin >> var1;
            std::cout << "digita um numero: ";
            std::cin >> var2;

                
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                continue;
            }

            erro = false;
        }
            float sum = (var1 + var2) / 2.0f;

            if (sum < 6.0f) {
                std::cout << "media eh baixa " << sum << std::endl;
            }
            else {
                std::cout << "media eh alta " << sum << std::endl;
            }

            std::cout << "digite start para continuar ou exit para sair\n" << std::endl;


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
