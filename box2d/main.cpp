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

b2Vec2 gravidade{0.0f, 0.3f};

struct Objetos
{
    SDL_FRect rect;
    SDL_Color color;

    b2BodyId body;
    b2ShapeId shape;

    bool state;
};

int main(int argc, char *argv[])
{
    renderer.winOpen("box2d", 640, 480);

    b2WorldId mundo;
    b2WorldDef worldDef;
    worldDef = b2DefaultWorldDef();

    worldDef.gravity = gravidade;

    mundo = b2CreateWorld(&worldDef);

    renderer.loadTextures();

    Objetos square;
        square.rect = {220.0f, 240.0f, 50.0f, 50.0f};
        b2BodyDef bodyDef = b2DefaultBodyDef();
        b2ShapeDef shapeDef = b2DefaultShapeDef();
        bodyDef.type = b2_dynamicBody;
        b2Polygon box = b2MakeBox(25.0f, 25.0f);
        bodyDef.position = {square.rect.x, square.rect.y};
        square.body = b2CreateBody(mundo, &bodyDef);
        square.shape = b2CreatePolygonShape(square.body, &shapeDef, &box);
        
    Objetos chao;
        chao.rect = {0.0f, 450.0f, 640.0f, 50.0f}; // X, Y, W, H
        b2BodyDef chaoDef = b2DefaultBodyDef();
        chaoDef.type = b2_staticBody;
        chaoDef.position = {320.0f, 475.0f};
        chao.body = b2CreateBody(mundo, &chaoDef);
        b2Polygon chaoBox = b2MakeBox(320.0f, 25.0f);
        chao.shape = b2CreatePolygonShape(chao.body, &shapeDef, &chaoBox);

    std::vector<SDL_FRect> paredes;
        paredes.push_back(chao.rect);

    while (renderer.running)
    {
        renderer.eventProcess();

        b2World_Step(mundo, 1.0f / 60.0f, 4);

        renderer.cleanScreen(0, 140, 0);

        b2Vec2 position = b2Body_GetPosition(square.body);
        square.rect.x = position.x - 25.0f;
        square.rect.y = position.y - 25.0f;

        renderer.drawWalls(paredes);
        renderer.drawSquare(square.rect);

        renderer.present();
    }

    b2DestroyWorld(mundo);



    renderer.close();
    return 0;
}