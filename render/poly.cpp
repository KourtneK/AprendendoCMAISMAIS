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

    Objetos triangle; // Definição de formato, peso e estado do triangulo
        triangle.rect = {220.0f, -240.0f, 50.0f, 50.0f};
        triangle.peso = 3.0f;
        triangle.state = false;

    SDL_Vertex vertice[3]; // Vertices do triangulo

        // Primeiro vertice
        vertice[0].position.x = triangle.rect.x + (triangle.rect.w / 2.0f);
        vertice[0].position.y = triangle.rect.y;
        vertice[0].color = {1.0f, 0.5f, 0.0f, 1.0f}; // Cor do vertice
        vertice[0].tex_coord = {0.0f, 0.0f}; // Não sei

        // Primeiro vertice
        vertice[1].position.x = triangle.rect.x;
        vertice[1].position.y = triangle.rect.y + triangle.rect.h;
        vertice[1].color = {1.0f, 0.5f, 0.0f, 1.0f};
        vertice[1].tex_coord = {0.0f, 0.0f};

        // Primeiro vertice
        vertice[2].position.x = triangle.rect.x + triangle.rect.w;
        vertice[2].position.y = triangle.rect.y + triangle.rect.h;
        vertice[2].color = {1.0f, 0.5f, 0.0f, 1.0f};
        vertice[2].tex_coord = {0.0f, 0.0f};

    // Retangulos
    SDL_FRect chao; // Chão
        chao.x = 0.0f;
        chao.y = 450.0f;
        chao.w = 640.0f;
        chao.h = 50.0f;

    SDL_FRect teto; // Teto
        teto.x = 0.0f;
        teto.y = 6.0f;
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

    std::vector <SDL_FRect> paredes;
    paredes.push_back(teto);
    paredes.push_back(paredeDireita);
    paredes.push_back(paredeEsquerda);

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

        // Renderiza o triangulo na tela usano 'RenderGeometry'
        SDL_RenderGeometry(render, nullptr, vertice, 3, nullptr, 0);

        // 5. Mostra tudo na tela
        SDL_RenderPresent(render);

        // Movimento. Muda as coordenadas diretamente com as setas
        if (keyState[SDL_SCANCODE_DOWN]) square.rect.y += 5.0f;
        if (keyState[SDL_SCANCODE_LEFT]) square.rect.x -= 5.0f;
        if (keyState[SDL_SCANCODE_RIGHT]) square.rect.x += 5.0f;

        // Velocidade de queda
        square.velocidade = square.velocidade + (gravidade * square.peso);
        triangle.velocidade = triangle.velocidade + (gravidade * triangle.peso);

        // Limitador de velocidade de queda
        // Do quadrado
        if (square.velocidade > 10.0f)
        { 
            square.velocidade = 10.0f; 
        }

        // Do triangulo
        if (triangle.velocidade > 10.0f)
        { 
            triangle.velocidade = 10.0f; 
        }

        // Incremento da velocidade
        square.rect.y += square.velocidade; // Do quadrado

        square.rect.y += square.velocidade; // Do triangulo

        // Colisão com as PAREDES ESQUERDA E DIREITA
        for (const auto& parede : paredes)
        {
            Colision::colisaoX(square.rect, parede, oldX); // quadrado
            Colision::colisaoX(triangle.rect, parede, oldX); // triangulo
        }

        // Colisão do TETO e CHÃO
        for (const auto& v : {chao, teto})
        {
            Colision::colisaoY(square.rect, v, oldY, square.velocidade, square.state); // quadrado
            Colision::colisaoY(triangle.rect, v, oldY, triangle.velocidade, triangle.state); // triangulo

           if (keyState[SDL_SCANCODE_UP] && square.state) 
           {
                square.velocidade = -6.0f;
                square.state = false;
            }
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