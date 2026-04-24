#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>
#include <float.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <box2d/box2d.h>
#include "render.h"

Renderizador renderer;

struct Objetos
{
    b2BodyId body;
    b2ShapeId shape;

    SDL_FRect rect;
    SDL_Color color;

    float forca;
    float peso;
    float massa;
    b2Vec2 velocidade{0.0f, 0.0f};

    bool state;
};

int main(int argc, char *argv[])
{
    


    return 0;
}