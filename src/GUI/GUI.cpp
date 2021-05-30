#include "GUI.hpp"

#include "SDL.h"

#include "../Display/Display.hpp"

constexpr int PIXEL_SIZE = 20;


SDL_Window* GUI::createWindow(void) {
    return SDL_CreateWindow(
        "chip8", 
        100, 100, 
        DisplaySpecs::PIXEL_WIDTH * PIXEL_SIZE, DisplaySpecs::PIXEL_HEIGHT * PIXEL_SIZE, 
        SDL_WINDOW_SHOWN
    );
}

SDL_Renderer* GUI::createRenderer(void) {
    return SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

void GUI::render(void) {
    SDL_RenderPresent(renderer);
}

void GUI::pumpEvents(void) {
    SDL_PumpEvents();
}

void GUI::drawPixel(int x, int y, int red, int green, int blue) {
    SDL_Rect r;
    r.x = x * PIXEL_SIZE;
    r.y = y * PIXEL_SIZE;
    r.w = r.h = PIXEL_SIZE;

    SDL_SetRenderDrawColor(renderer, red, green, blue, 255);
    SDL_RenderFillRect(renderer, &r);
}

bool GUI::hasExit(void) {
    SDL_Event ev;
    return (SDL_PollEvent(&ev) != 0 && ev.type == SDL_QUIT) 
            || (isKeyPressed(SDL_SCANCODE_ESCAPE));
}

void GUI::closeWindow(void) {
    SDL_DestroyWindow(window);
}