#include <iostream>
#include <string>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <time.h>
#include <float.h>


// ENTENDENDO A LIB SDL3

int main(int argc, char *argv[])
{
    // 1. Liga o render de video
    SDL_Init(SDL_INIT_VIDEO);

    // 2. Cria a Janela e o Renderizador
    SDL_Window* window = nullptr;
    SDL_Renderer* render = nullptr;

    // Título da janela, Largura, Altura, "Flags" (não sei o que são flags)
    // SDL_WINDOW_RESIZABLE: Permite puxar as bordas para aumentar a janela.
    // SDL_WINDOW_MAXIMIZED: Inicia a janela já ocupando a tela toda.
    SDL_CreateWindowAndRenderer("Ola", 640, 480, SDL_WINDOW_RESIZABLE, &window, &render);

    // 6. Loop de eventos para manter a janela aberta e funcional
    bool winOpen = true;
    SDL_Event evento;

    SDL_FRect square; // Quadrado
        square.x = 220.0f;
        square.y = 340.0f;
        square.w = 50.0f;
        square.h = 50.0f;

    SDL_FRect chao; // Chão
        chao.x = 0.0f;
        chao.y = 450.0f;
        chao.w = 640.0f;
        chao.h = 50.0f;

    SDL_FRect teto; // Teto
        teto.x = 0.0f;
        teto.y = 10.0f;
        teto.w = 640.0f;
        teto.h = 50.0f;

    SDL_FRect paredeDireita; // Parede direita
        paredeDireita.x = 570.0f;
        paredeDireita.y = 0.0f;
        paredeDireita.w = 50.0f;
        paredeDireita.h = 490.0f;

    SDL_FRect paredeEsquerda; // Parede esquerda
        paredeEsquerda.x = 0.0f;
        paredeEsquerda.y = 0.0f;
        paredeEsquerda.w = 50.0f;
        paredeEsquerda.h = 490.0f;

    float gravidade;
    gravidade = 0.3f;

    float squarePeso;
    squarePeso = 0.0f;
    squarePeso += gravidade;

    float velocidade;
    velocidade = 0.0f;

    while (winOpen)
    {
        while (SDL_PollEvent(&evento))
        {
            if (evento.type == SDL_EVENT_QUIT)
            {
                winOpen = false;
            }
        }

        const bool* keyState = SDL_GetKeyboardState(NULL); // verifica o estado de todas as teclas (0 para solta | 1 para pressionada)

        if (keyState[SDL_SCANCODE_UP]) square.y -= 5.0f;
        if (keyState[SDL_SCANCODE_SPACE]) square.y -= 5.0f;
        if (keyState[SDL_SCANCODE_DOWN]) square.y += 5.0f;
        if (keyState[SDL_SCANCODE_LEFT]) square.x -= 5.0f;
        if (keyState[SDL_SCANCODE_RIGHT]) square.x += 5.0f;


        // 3. Chama o renderizador escolhe a cor para a tela (RGB(vermelho, verde, azul), Opacidade)
        // Verde escuro(0, 140, 0, 255)
        SDL_SetRenderDrawColor(render, 0, 140, 0, 255);

        // 4. Seta a cor escolhida na tela inteira
        SDL_RenderClear(render);

        // Renderiza o CHÃO
        SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
        SDL_RenderFillRect(render, &chao);

        // Renderiza o TETO
        SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
        SDL_RenderFillRect(render, &teto);

        // Renderiza a PAREDE DIREITA
        SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
        SDL_RenderFillRect(render, &paredeDireita);

        // Renderiza a PAREDE ESQUERDA
        SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
        SDL_RenderFillRect(render, &paredeEsquerda);

        // Seta a cor do quadrado e renderiza ele na tela
        SDL_SetRenderDrawColor(render, 0, 0, 140, 255);
        SDL_RenderFillRect(render, &square);

        // 5. Mostra tudo na tela
        SDL_RenderPresent(render);

        // Gravidade
        velocidade += gravidade;
        square.y += velocidade;

        // Colisão do quadrado com o CHÃO
        if (square.y + square.h >= chao.y)
        {
            square.y = chao.y - square.h;
            
            if (velocidade > 5.0f)
            {
                velocidade = gravidade;
            }               
        }

        // Colisão do quadrdo com o TETO
        if (square.y <= teto.y + teto.h)
        {
            square.y = teto.y + teto.h;
        }

        // Colisão com a PAREDE ESQUERDA
        if (square.x <= paredeEsquerda.x + paredeEsquerda.w)
        {
            square.x = paredeEsquerda.x + paredeEsquerda.w;
        }
        

        // Colisão com a PAREDE DIREITA
        if (square.x + square.w >= paredeDireita.x)
        {
            square.x = paredeDireita.x - square.w;
        }




        SDL_Delay(16); // tempo de resposta da janela ~60 fps
    }

    SDL_DestroyRenderer(render); // Destroi o renderizador (não renderiza mais nada na janela)
    SDL_DestroyWindow(window); // Destroi a janela (fecha a janela)
    SDL_Quit(); // Para o motor de renderização da lib SDL3




    return 0;
}



/*

if (square.x >= paredeDireita.x)
{
    square.x = paredeDireita.x - square.x;   
}

*/