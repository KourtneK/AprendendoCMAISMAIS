#include <iostream>
#include <string>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <time.h>
#include <float.h>


// ENTENDENDO A LIB SDL3

int main(int argc, char const *argv[])
{
    // 1. Liga o render de video
    SDL_Init;

    // 2. Cria a Janela e o Renderizador
    SDL_Window* window = nullptr;
    SDL_Renderer* render = nullptr;

    // Título da janela, Largura, Altura, "Flags" (não sei o que são flags)
    SDL_CreateWindowAndRenderer("Ola", 640, 480, 0, &window, &render);

    // 3. Chama o renderizador escolhe a cor para a tela (RGB(vermelho, verde, azul), Opacidade)
    // Verde escuro(0, 140, 0, 255)
    SDL_SetRenderDrawColor(render, 0, 140, 0, 255);

    // 4. Seta a cor escolhida na tela inteira
    SDL_RenderClear(render);

    // 5. Mostra a cor na tela
    SDL_RenderPresent(render);

    // 6. Seta um tempo para a janela fechar
    // 3 segundos (3000ms)
    SDL_Delay(3000); // Tempo em milissegundos (ms)

    SDL_DestroyRenderer(render); // Destroi o renderizador (não renderiza mais nada na janela)
    SDL_DestroyWindow(window); // Destroi a janela (fecha a janela)
    SDL_Quit(); // Para o motor de renderização da lib SDL3

    return 0;
}
