#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>
#include <float.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <box2d/box2d.h>

struct Objetos
{
    b2BodyId body;   

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
    SDL_Init(SDL_INIT_VIDEO);

    // 2. Cria a Janela e o Renderizador
    SDL_Window* window = nullptr;
    SDL_Renderer* render = nullptr;

    // Título da janela, Largura, Altura, "Flags" (não sei o que são flags)
    SDL_CreateWindowAndRenderer("box2d", 640, 480, SDL_WINDOW_RESIZABLE, &window, &render);

    // 6. Loop de eventos para manter a janela aberta e funcional
    bool winOpen = true;
    SDL_Event evento;

    b2Vec2 gravidade{0.0f, 0.3f};

    Objetos square;
        square.rect = {220.0f, 240.0f, 50.0f, 50.0f}; // X, Y, W, H
        square.massa = 1.0f;
        square.peso = massa * gravidade;
        b2Body_GetLinearVelocity(square.body);
        square.state = false;

    // Criação do mundo na tela
    b2WorldDef WorldDef = b2DefaultWorldDef(); // Define o mundo padrão
    WorldDef.gravity = gravidade; // Define a função de gravidade
    b2WorldId worldId = b2CreateWorld(&WorldDef);

    // Define o objeto
    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = {square.rect.x, square.rect.y};

    square.body = b2CreateBody(worldId, &bodyDef);

    b2Body_SetGravityScale(square.body, square.peso);

















    

    // Definição de paredes, chão e teto
    SDL_FRect chao = {0.0f, 450.0f, 640.0f, 50.0f}; // X, Y, W, H    
    SDL_FRect teto = {0.0f, 0.0f, 640.0f, 50.0f}; // X, Y, W, H
    SDL_FRect paredeDireita = {590.0f, 0.0f, 50.0f, 490.0f}; // X, Y, W, H
    SDL_FRect paredeEsquerda = {0.0f, 0.0f, 50.0f, 490.0f}; // X, Y, W, H

    //definição de paredes, chão e teto como objetos vetoriais
    std::vector <SDL_FRect> paredes;
        SDL_Surface* surfaceMapa = SDL_LoadBMP("tilemap.bmp");

        if (surfaceMapa) 
        {
            // Garante que o formato de cor seja padrão para não dar erro de leitura
            SDL_Surface* surfaceFormatada = SDL_ConvertSurface(surfaceMapa, SDL_PIXELFORMAT_RGBA8888);
            SDL_DestroySurface(surfaceMapa);

            if (surfaceFormatada) 
            {
                // Ponteiro para os dados crus dos pixels
                Uint32* pixels = (Uint32*)surfaceFormatada->pixels;
                const int largura = surfaceFormatada->w;
                const int altura = surfaceFormatada->h;

                for (int y = 0; y < altura; y++) 
                {
                    for (int x = 0; x < largura; x++) 
                    {
                        // A "mágica" vanilla para achar o pixel na memória linear
                        Uint32 pixelCor = pixels[y * largura + x];
                        Uint8 r, g, b, a;
                        
                        // Extrai as cores do pixel
                        SDL_GetRGBA(pixelCor, SDL_GetPixelFormatDetails(surfaceFormatada->format), NULL, &r, &g, &b, &a);

                        float posX = x * 50.0f;
                        float posY = y * 50.0f;

                        // Se o pixel for PRETO (0,0,0) -> Parede
                        if (r == 0 && g == 0 && b == 0) 
                        {
                            paredes.push_back({posX, posY, 50.0f, 50.0f});
                        }
                        // Se o pixel for VERMELHO (255,0,0) -> Spawn do Player
                        else if (r == 255 && g == 0 && b == 0) 
                        {
                            square.rect.x = posX;
                            square.rect.y = posY;
                        }
                    }
                }
                SDL_DestroySurface(surfaceFormatada);
            }
        } 
        else 
        {
            SDL_Log("ERRO: Nao encontrei o mapa.bmp na pasta!");
        }

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