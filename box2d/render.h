#ifndef RENDER_H
#define RENDER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>
#include <float.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <box2d/box2d.h>

struct Renderizador
{
    SDL_Window* window = nullptr;
    SDL_Renderer* render = nullptr;
    SDL_Texture* squareTexture = nullptr;
    SDL_Texture* wallTexture = nullptr;

    bool running = true;

    // 1. Inicializa o motor de vídeo e a janela (Suporte a bordas puxáveis)
    void winOpen(const char* titulo, int w, int h)
    {
        SDL_Init(SDL_INIT_VIDEO);

        // Título, Largura, Altura, Flags e ponteiros para a memória da janela/render
        SDL_CreateWindowAndRenderer(titulo, w, h, SDL_WINDOW_RESIZABLE, &window, &render);
    }

    // Processa os eventos da janela e do teclado para saída
    void eventProcess()
    {
        SDL_Event evento;
        while (SDL_PollEvent(&evento))
        {
            if (evento.type == SDL_EVENT_QUIT)
            {
                running = false;
            }

            if (evento.type == SDL_EVENT_KEY_DOWN)
            {
                if (evento.key.key == SDLK_ESCAPE)
                {
                    running = false;
                }
            }
        }
    }

    // 2. Converte BMP em dados de colisão e spawn
    void mapProcess(const char* caminho, std::vector<SDL_FRect>& paredes, float& playerX, float& playerY)
    {
        SDL_Surface* surfaceMap = SDL_LoadBMP(caminho);

        if (surfaceMap)
        {
            // Converte para RGBA8888 para garantir que a leitura de cores seja padrão e não dê erro
            SDL_Surface* surfaceFormatada = SDL_ConvertSurface(surfaceMap, SDL_PIXELFORMAT_RGBA8888);

            SDL_DestroySurface(surfaceMap);

            if (surfaceFormatada)
            {
                // Ponteiro para os dados crus dos pixels na memória linear
                Uint32* pixels = (Uint32*)surfaceFormatada->pixels;

                for (int y = 0; y < surfaceFormatada->h; y++)
                {
                    for (int x = 0; x < surfaceFormatada->w; x++)
                    {
                        // Multiplica Y pelo ponteiro do mapa processado e soma W + X
                        Uint32 pixelCor = pixels[y * surfaceFormatada->w + x];

                        Uint8 r, g, b, a;

                        SDL_GetRGBA(pixelCor, SDL_GetPixelFormatDetails(surfaceFormatada->format), NULL, &r, &g, &b, &a);

                        // Se o pixel for PRETO -> Guarda um retângulo de 50x50 no vetor
                        if (r == 0 && g == 0 && b == 0)
                        {
                            paredes.push_back({x * 50.0f, y * 50.0f, 50.0f, 50.0f});
                        }
                        // Se o pixel for VERMELHO -> Define a coordenada de nascimento do quadrado
                        else if (r == 255 && g == 0 && b == 0)
                        {
                            playerX = x * 50.0f; playerY = y * 50.0f;
                        }
                    }
                }

                SDL_DestroySurface(surfaceFormatada);

            }
        }
    }

    // 3. Traz as imagens da RAM (Surface) para a memória da GPU (Texture)
    void loadTextures()
    {
        SDL_Surface* surfaceSquare = SDL_LoadBMP("pigui.bmp"); 
        SDL_Surface* surfaceWall = SDL_LoadBMP("tijolo.bmp");

        // Log de erro no terminal caso o carregamento da textua falhe
        if (!surfaceSquare || !surfaceWall)
        {
            SDL_Log("erro ao carregar bmp: %s", SDL_GetError());
        }

        squareTexture = SDL_CreateTextureFromSurface(render, surfaceSquare);
        wallTexture = SDL_CreateTextureFromSurface(render, surfaceWall);

        // Limpa a RAM
        SDL_DestroySurface(surfaceSquare);
        SDL_DestroySurface(surfaceWall);
    }

    // 4. Escolhe a cor e limpa o frame anterior para o novo desenho
    void cleanScreen(Uint8 r, Uint8 g, Uint8 b)
    {
        SDL_SetRenderDrawColor(render, r, g, b, 255); // Ex: Verde escuro (0, 140, 0)

        SDL_RenderClear(render);
    }

    // 5. Desenha as paredes no vetor
    void drawWalls(const std::vector<SDL_FRect>& paredes)
    {
        for (const auto& parede : paredes)
        {
            SDL_RenderTexture(render, wallTexture, NULL, &parede);
        }
    }

    // 6. Renderiza o Pinguim ou um retângulo azul se a imagem sumir
    void drawSquare(const SDL_FRect& rect)
    {
        if (squareTexture)
        {
            SDL_RenderTexture(render, squareTexture, NULL, &rect);
        }
        else 
        {
            SDL_SetRenderDrawColor(render, 0, 0, 140, 255); // Azul RGBA

            SDL_RenderFillRect(render, &rect);
        }
    }

    // 7. Renderiza tudo
    void present()
    {
        SDL_RenderPresent(render);
    }

    // 8. Fecha o motor e limpa a memória ao sair
    void close()
    {
        SDL_DestroyTexture(squareTexture);
        SDL_DestroyTexture(wallTexture);
        SDL_DestroyRenderer(render);
        SDL_DestroyWindow(window);

        SDL_Quit(); // Para o motor de renderização
    }
};

#endif