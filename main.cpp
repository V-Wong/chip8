#include <iostream>

#include "SDL.h"

#include "src/Emulator/Emulator.h"
#include "src/Memory/Memory.h"
#include "src/Stack/Stack.h"
#include "src/Display/Display.h"

constexpr int PIXEL_SIZE = 20;

int main(int, char **) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow(
        "chip8", 
        100, 100, 
        DisplaySpecs::PIXEL_WIDTH * PIXEL_SIZE, DisplaySpecs::PIXEL_HEIGHT * PIXEL_SIZE, 
        SDL_WINDOW_SHOWN
    );
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    for (int i = 0; i < 64; i++) {
        for (int j = 0; j < 32; j++) {
            SDL_Rect r;
            r.x = i * PIXEL_SIZE;
            r.y = j * PIXEL_SIZE;
            r.w = r.h = PIXEL_SIZE;

            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
            SDL_RenderFillRect(renderer, &r);
            SDL_RenderPresent(renderer);
            SDL_Delay(50);
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
}
