#include <unistd.h>


int main()
{
    char key;

    system("cls");
    while (read(STDIN_FILENO, &key, 1) == 1 && key != 'q');

    
    


    return 0;
}