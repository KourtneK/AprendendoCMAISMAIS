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


// Definição da etrutura de objetos
struct Objetos
{
    SDL_FRect rect; // Define as variaveis renderização, tamanho, e posição do objeto
    SDL_Color color; // Define variavel cor do obejeto

    b2BodyId body; // Define o corpo do objeeto
    b2ShapeId shape; // Define a forma do objeto

    bool state; // Define o estado do objeto (estar ou não no encostando no chão)
};

int main(int argc, char *argv[])
{
    renderer.winOpen("box2d", 640, 480); // Define a abertura, titulo e resolução da janela

    b2WorldId mundo; // Criação do mundo
    b2WorldDef worldDef; // Definição do mundo
    worldDef = b2DefaultWorldDef(); // Definição de criação padrão do mundo

    worldDef.gravity = gravidade; // Definindo a gravidade do mundo

    mundo = b2CreateWorld(&worldDef); // Definindo o mundo como criado. Definindo a definição do mundo como ponteiro

    renderer.loadTextures(); // Renderizando as texturas

    // Definição do objeto square    
    Objetos square;
        square.rect = {220.0f, 240.0f, 50.0f, 50.0f};
        b2BodyDef bodyDef = b2DefaultBodyDef();
        b2ShapeDef shapeDef = b2DefaultShapeDef();
        bodyDef.type = b2_dynamicBody;
        b2Polygon box = b2MakeBox(25.0f, 25.0f); // Forma do square
        bodyDef.position = {square.rect.x, square.rect.y};
        square.body = b2CreateBody(mundo, &bodyDef);
        square.shape = b2CreatePolygonShape(square.body, &shapeDef, &box);
        
    // Definição do objeto chão
    Objetos chao;
        chao.rect = {0.0f, 450.0f, 640.0f, 50.0f}; // X, Y, W, H
        b2BodyDef chaoDef = b2DefaultBodyDef();
        chaoDef.type = b2_staticBody;
        chaoDef.position = {320.0f, 475.0f};
        chao.body = b2CreateBody(mundo, &chaoDef);
        b2Polygon chaoBox = b2MakeBox(320.0f, 25.0f); // Forma do chão
        chao.shape = b2CreatePolygonShape(chao.body, &shapeDef, &chaoBox);

    // Definindo o vetor de paredes        
	 std::vector<SDL_FRect> paredes;
        paredes.push_back(chao.rect); // Definindo o chão como vetor

        
    while (renderer.running)
    {
        renderer.eventProcess(); // Processa a entrada 'Esc' do teclado

        b2World_Step(mundo, 1.0f / 60.0f, 4); // Define quantos FPS o mundo ira rodar (60 fps)

        renderer.cleanScreen(0, 140, 0); // Define a tela omo verde e limpa ela

        b2Vec2 position = b2Body_GetPosition(square.body); // Define um vetor da lib 'box2d'. Pega a posição do eixo 'X' e 'Y' internos do square
        square.rect.x = position.x - 25.0f;
        square.rect.y = position.y - 25.0f;

        if (SDL_SCANCODE_LEFT)
        {
            worldDef = {5.0f, 0.0f};            
        }
        
        renderer.drawWalls(paredes); // Renderiza o vetor de paredes
        renderer.drawSquare(square.rect); // Renderiza o objeto entidade square

        renderer.present(); // Apresenta tudo na tela
    }

    


    b2DestroyWorld(mundo); // Buffer que limpa o lixo do mundo da memoria
    renderer.close(); // Limpa o buffer da tela da memoria ram
    return 0;
}
