#include <iostream>
#include <string>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <time.h>
#include <float.h>
#include <vector>
#include "colision.h"

// ENTENDENDO A LIB SDL3

// SDL_WINDOW_RESIZABLE: Permite puxar as bordas para aumentar a janela.
// SDL_WINDOW_MAXIMIZED: Inicia a janela já ocupando a tela toda.

// Variaveis globais de estrutura de objetos
struct Objetos
{
    SDL_FRect rect;
    float peso;
    float velocidadeY;
    float velocidadeX;

    int qntPulos;

    bool state;
    bool stateKeyHold;
};

int main(int argc, char *argv[])
{
    // 1. Liga o render de video
    SDL_Init(SDL_INIT_VIDEO);

    // 2. Cria a Janela e o Renderizador
    SDL_Window* window = nullptr;
    SDL_Renderer* render = nullptr;

    // Título da janela, Largura, Altura, "Flags" (não sei o que são flags)
    SDL_CreateWindowAndRenderer("Poly Game", 640, 480, SDL_WINDOW_RESIZABLE, &window, &render);

    // 6. Loop de eventos para manter a janela aberta e funcional
    bool winOpen = true;
    SDL_Event evento;

    // Variavel global de gravidade
    float gravidade;
    gravidade = 0.3f;

    // Variavel global para inercia/atrito
    float inercia;
    inercia = 1.0f;

    // Definição dos objetos
    Objetos square; // Definição de formato, peso e estado do quadrado
        square.rect = {220.0f, 340.0f, 50.0f, 50.0f};
        square.peso = 1.0f;
        square.velocidadeY = 0.0f;
        square.velocidadeX = 0.0f;
        square.qntPulos = 0;
        square.state = false;
        square.stateKeyHold = false;
    
    // Definição de paredes, chão e teto
    SDL_FRect chao = {0.0f, 450.0f, 640.0f, 50.0f}; // X, Y, W, H    
    SDL_FRect teto = {0.0f, 0.0f, 640.0f, 50.0f}; // X, Y, W, H
    SDL_FRect paredeDireita = {590.0f, 0.0f, 50.0f, 490.0f}; // X, Y, W, H
    SDL_FRect paredeEsquerda = {0.0f, 0.0f, 50.0f, 490.0f}; // X, Y, W, H

    //definição de paredes, chão e teto como objetos vetoriais
    std::vector <SDL_FRect> paredes;
        paredes.push_back(chao);
        paredes.push_back(teto);
        paredes.push_back(paredeDireita);
        paredes.push_back(paredeEsquerda);

    // Definição da textura
    SDL_Surface* surfaceSquare;
    SDL_Surface* surfaceWall;
    surfaceSquare = SDL_LoadBMP("pigui.bmp");
    surfaceWall = SDL_LoadBMP("tijolo.bmp");

    // tenta carregar a textura, se falhar retorna um log de erro
    if (!surfaceSquare)
    {
        SDL_Log("erro ao carregar bmp: %s", SDL_GetError());
    }

    if (!surfaceWall)
    {
        SDL_Log("erro ao carregar bmp: %s", SDL_GetError());
    }
    
    // Defininto imagens bmp como textura
    SDL_Texture* squareTexture;
    SDL_Texture* wallTexture;
    squareTexture = SDL_CreateTextureFromSurface(render, surfaceSquare);
    wallTexture = SDL_CreateTextureFromSurface(render, surfaceWall);

    // Limpa as texturas da memoria ram
    SDL_DestroySurface(surfaceSquare);
    SDL_DestroySurface(surfaceWall);

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

        // Limitador de velocidadeY
        if (square.velocidadeY > 10.0f)
        {
            square.velocidadeY = 10.0f;
        }
        
        // Limitador de velocidade+X
        if (square.velocidadeX > 5.0f)
        {
            square.velocidadeX = 5.0f;
        }

        // Limitador de velocidade-X
        if (square.velocidadeX < -5.0f)
        {
            square.velocidadeX = -5.0f;
        }

        // Força aplicada em '-X'
        if (keyState[SDL_SCANCODE_LEFT])
        {
            if (square.velocidadeX > 0) // Atrito infinito
            {
                square.velocidadeX = 0;
            }

            square.velocidadeX = square.velocidadeX - (inercia * square.peso);
        }
        // Força aplicada em '+X'
        else if (keyState[SDL_SCANCODE_RIGHT])
        {
            if (square.velocidadeX < 0)
            {
                square.velocidadeX = 0;
            }   

            square.velocidadeX = square.velocidadeX + (inercia * square.peso);
        }
        else // Se soltar left/right zera a velocidade
        {
            square.velocidadeX = 0.0f;
        }

        // Velocidade de queda
        square.velocidadeY = square.velocidadeY + (gravidade * square.peso);

        // Incremento da velocidadeX e Y
        square.rect.y += square.velocidadeY;
        square.rect.x += square.velocidadeX;

        // Colisão com as paredes, chão e teto
        for (const auto& parede : paredes)
        {
            Colision::colisaoX(square.rect, parede, oldX);
            Colision::colisaoY(square.rect, parede, oldY, square.velocidadeY, square.state);
        }

        // Força aplicada em '-Y' ( tem que ser iniciada depois da col)
        if (keyState[SDL_SCANCODE_UP])
        {
            if (!square.stateKeyHold)
            {
                if (square.state)
                {
                    square.velocidadeY = -5.0f;
                    square.state = false;
                    square.qntPulos = 1;
                }
                else if (square.qntPulos > 0)
                {
                    square.velocidadeY = -5.0f;
                    square.qntPulos = 0;
                }
            }

            square.stateKeyHold = true;

        }
        else
        {
            square.stateKeyHold = false;
        }

        // 3. Chama o renderizador escolhe a cor para a tela (RGB(vermelho, verde, azul), Opacidade)
        // Verde escuro(0, 140, 0, 255)
        SDL_SetRenderDrawColor(render, 0, 140, 0, 255);

        // 4. Seta a cor escolhida na tela inteira
        SDL_RenderClear(render);

        // Renderiza a textura de paredes, teto, e chão
        SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
        for (const auto& parede : paredes)
        {
            SDL_RenderTexture(render, wallTexture, NULL, &parede);
        }
        
        // Renderiza a textura
        if (squareTexture != nullptr)
        {
            SDL_RenderTexture(render, squareTexture, NULL, &square.rect);
        }
        else // Se não conseguir renderizar a textura renderiza um quadrado azul
        {
            SDL_SetRenderDrawColor(render, 0, 0, 140, 255);
            SDL_RenderFillRect(render, &square.rect);    
        }
        
        SDL_RenderPresent(render);
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
