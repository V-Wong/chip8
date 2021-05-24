#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>

#include "SDL.h"

#include "src/Emulator/Emulator.h"
#include "src/Memory/Memory.h"
#include "src/Stack/Stack.h"
#include "src/Display/Display.h"

constexpr int PIXEL_SIZE = 20;

std::vector<uint8_t> readFile();

int main(int, char **) {
    Emulator e;
    e.load(readFile());

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

    for (int x = 0; x < 50; x++) {
        for (int i = 0; i < DisplaySpecs::PIXEL_WIDTH; i++) {
            for (int j = 0; j < DisplaySpecs::PIXEL_HEIGHT; j++) {
                if (e.getPixel(i, j)) {
                    SDL_Rect r;
                    r.x = i * PIXEL_SIZE;
                    r.y = j * PIXEL_SIZE;
                    r.w = r.h = PIXEL_SIZE;

                    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                    SDL_RenderFillRect(renderer, &r);
                    SDL_RenderPresent(renderer);
                }
            }
        }
        e.run();
        SDL_Delay(100);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
}

std::vector<uint8_t> readFile() {
    std::ifstream input("./ibm.ch8", std::ios::binary);

    std::vector<uint8_t> bytes(
         (std::istreambuf_iterator<char>(input)),
         (std::istreambuf_iterator<char>())
    );

    input.close();

    return bytes;
}