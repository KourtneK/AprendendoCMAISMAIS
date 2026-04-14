#ifndef COLISION_H
#define COLISION_H
#include <iostream>
#include <string>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <time.h>
#include <float.h>
#include <vector>

struct Colision
{
    // Colisão  com todas as paredes no eixo 'X'
    static void colisaoX(SDL_FRect& rect, const SDL_FRect& wall, float oldX)
    {
        if (SDL_HasRectIntersectionFloat(&rect, &wall))
        {
            // Colisão da PAREDE ESQUERDA
            if (oldX + rect.w <= wall.x)
            {
                rect.x = wall.x - rect.w;
            }

            // Colisão da PAREDE DIREITA
            else if (oldX >= wall.x + wall.w)
            {
                rect.x = wall.x + wall.w;
            }
        }
        
    }

    // Colisão  com todas as paredes no eixo 'Y'
    static void colisaoY(SDL_FRect& rect, const SDL_FRect& wall, float oldY, float& velocidade, bool& state)
    {
        if (SDL_HasRectIntersectionFloat(&rect, &wall))
        {
            // Colisão do CHÃO
            if (oldY + rect.h <= wall.y)
            {
                rect.y = wall.y - rect.h;

                velocidade = 0.0f;

                state = true;
            }

            // Colisão do TETO
            else if (oldY >= wall.y + wall.h)
            {
                rect.y = wall.y + wall.h;
                velocidade = 0.0f;
            }
        }
    }
};


#endif