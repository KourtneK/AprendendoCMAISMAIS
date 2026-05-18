#include <iostream>
#include <string>
#include <fstream>
#include <SDL3\SDL.h>
#include <SDL3\SDL_main.h>
#include "render.h"

Renderizador renderer;

int main(int argc, char** argv)
{
    renderer.winOpen("Terminal", 1200, 640);

    while (renderer.running)
    {
        renderer.eventProcess();


    }

    return 0;
}
