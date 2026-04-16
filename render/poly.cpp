#include <iostream>
#include <string>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <time.h>
#include <float.h>
#include <vector>
#include "colision.h"

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
    SDL_CreateWindowAndRenderer("Poly Game", 640, 480, SDL_WINDOW_RESIZABLE, &window, &render);

    // 6. Loop de eventos para manter a janela aberta e funcional
    bool winOpen = true;
    SDL_Event evento;

    // Variavel global de gravidade
    float gravidade;
    gravidade = 0.3f;

    // Variaveis globais de estrutura de objetos
    struct Objetos
    {
        SDL_FRect rect;
            float peso;
            float velocidade;

            bool state;
    };

    // Definição dos objetos
    Objetos square; // Definição de formato, peso e estado do quadrado
        square.rect = {220.0f, 340.0f, 50.0f, 50.0f};
        square.peso = 1.0f;
        square.state = false;

    // Retangulos
    SDL_FRect chao; // Chão
        chao.x = 0.0f;
        chao.y = 450.0f;
        chao.w = 640.0f;
        chao.h = 50.0f;
    
    SDL_FRect teto = {0.0f, 0.0f, 640.0f, 50.0f};
    SDL_FRect paredeDireita = {570.0f, 0.0f, 50.0f, 490.0f};
    SDL_FRect paredeEsquerda = {0.0f, 0.0f, 50.0f, 490.0f};

    std::vector <SDL_FRect> paredes;
        paredes.push_back(teto) {0.0f, 0.6f, 640.0f, 50.0f};
        paredes.push_back(paredeDireita) {570.0f, 0.0f, 50.0f, 490.0f};
        paredes.push_back(paredeEsquerda) {0.0f, 0.0f, 50.0f, 490.0f};

    while (winOpen)
    {
        while (SDL_PollEvent(&evento))
        {
            if (evento.type == SDL_EVENT_QUIT)
            {
                winOpen = false;
            }

            // Sair com 'esc'
            if (evento.type == SDL_EVENT_KEY_DOWN)
            {
                if (evento.key.key == SDLK_ESCAPE)
                {
                    winOpen = false;
                }
            }
        }

        const bool* keyState = SDL_GetKeyboardState(NULL); // verifica o estado de todas as teclas (0 para solta | 1 para pressionada)

        float oldX;
        float oldY;
        oldX = square.rect.x;
        oldY = square.rect.y;

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
        SDL_RenderFillRect(render, &square.rect);

        // 5. Mostra tudo na tela
        SDL_RenderPresent(render);

        // Movimento. Muda as coordenadas diretamente com as setas
        if (keyState[SDL_SCANCODE_DOWN]) square.rect.y += 5.0f;
        if (keyState[SDL_SCANCODE_LEFT]) square.rect.x -= 5.0f;
        if (keyState[SDL_SCANCODE_RIGHT]) square.rect.x += 5.0f;

        // Velocidade de queda
        square.velocidade = square.velocidade + (gravidade * square.peso);

        // Limitador de velocidade de queda
        if (square.velocidade > 10.0f)
        {
            square.velocidade = 10.0f; 
        }

        // Incremento da velocidade
        square.rect.y += square.velocidade; // Do quadrado

        // Colisão com as PAREDES ESQUERDA E DIREITA
        for (const auto& parede : paredes)
        {
            Colision::colisaoX(square.rect, parede, oldX); // quadrado
        }

        if (keyState[SDL_SCANCODE_UP] && square.state) 
            {
                square.velocidade = -6.0f;
                square.state = false;
            }

        // Colisão do TETO e CHÃO
        for (const auto& vito : {chao, teto})
        {
            Colision::colisaoY(square.rect, vito, oldY, square.velocidade, square.state); // quadrado
        }



        SDL_Delay(16); // tempo de resposta da janela ~60 fps
    }

    SDL_DestroyRenderer(render); // Destroi o renderizador (não renderiza mais nada na janela)
    SDL_DestroyWindow(window); // Destroi a janela (fecha a janela)
    SDL_Quit(); // Para o motor de renderização da lib SDL3



    return 0;
}



/*

if (square.rect.x >= paredeDireita.x)
{
    square.rect.x = paredeDireita.x - square.x;   
}

*/