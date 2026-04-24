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

    // 1. Ferramenta: Inicializa o motor de vídeo e a janela
    void winOpen(const char* titulo, int w, int h)
    {
        SDL_Init(SDL_INIT_VIDEO);

        SDL_CreateWindowAndRenderer(titulo, w, h, SDL_WINDOW_RESIZABLE, &window, &render);
    }

    // 2. Ferramenta: Carrega o tilemap.bmp e preenche o seu vector
    void mapProcess(const char* caminho, std::vector<SDL_FRect>& paredes, float& playerX, float& playerY)
    {
        SDL_Surface* surfaceMap = SDL_LoadBMP(caminho);

        if (surfaceMap)
        {
            SDL_Surface* surfaceFormatada = SDL_ConvertSurface(surfaceMap, SDL_PIXELFORMAT_RGBA8888);

            SDL_DestroySurface(surfaceMap);

            if (surfaceFormatada)
            {
                Uint32* pixels = (Uint32*)surfaceFormatada->pixels;

                for (int y = 0; y < surfaceFormatada->h; y++)
                {
                    for (int x = 0; x < surfaceFormatada->w; x++)
                    {
                        Uint32 pixelCor = pixels[y * surfaceFormatada->w + x];
                        Uint8 r, g, b, a;

                        SDL_GetRGBA(pixelCor, SDL_GetPixelFormatDetails(surfaceFormatada->format), NULL, &r, &g, &b, &a);

                        if (r == 0 && g == 0 && b == 0) paredes.push_back({x * 50.0f, y * 50.0f, 50.0f, 50.0f});

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

    // 3. Ferramenta: Carrega as texturas dos BMPs
    void loadTextures()
    {
        SDL_Surface* sSquare = SDL_LoadBMP("pigui.bmp");
        SDL_Surface* sWall = SDL_LoadBMP("tijolo.bmp");

        squareTexture = SDL_CreateTextureFromSurface(render, sSquare);
        wallTexture = SDL_CreateTextureFromSurface(render, sWall);

        SDL_DestroySurface(sSquare);
        SDL_DestroySurface(sWall);
    }

    // 4. Ferramentas de Desenho Granulares (Para você alternar com a física)
    void limparTela(Uint8 r, Uint8 g, Uint8 b)
    {
        SDL_SetRenderDrawColor(render, r, g, b, 255);

        SDL_RenderClear(render);
    }

    void desenharParedes(const std::vector<SDL_FRect>& paredes)
    {
        for (const auto& parede : paredes) SDL_RenderTexture(render, wallTexture, NULL, &parede);
    }

    void drawSquare(const SDL_FRect& rect)
    {
        if (squareTexture)
        {
        SDL_RenderTexture(render, squareTexture, NULL, &rect);
        }
        else 
        {
            SDL_SetRenderDrawColor(render, 0, 0, 140, 255); SDL_RenderFillRect(render, &rect);
        }
    }

    void present()
    {
        SDL_RenderPresent(render);
    }

    // 5. Ferramenta: Cleanup final
    void close()
    {
        SDL_DestroyTexture(squareTexture);
        SDL_DestroyTexture(wallTexture);
        SDL_DestroyRenderer(render);
        SDL_DestroyWindow(window);

        SDL_Quit();
    }
};

#endif