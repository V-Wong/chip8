#include "GUI.hpp"

#include "SDL.h"

#include "../Display/Display.hpp"

auto constexpr PIXEL_SIZE = 20;


auto GUI::createWindow(void) -> SDL_Window* {
    return SDL_CreateWindow(
        "chip8", 
        100, 100, 
        DisplaySpecs::PIXEL_WIDTH * PIXEL_SIZE, DisplaySpecs::PIXEL_HEIGHT * PIXEL_SIZE, 
        SDL_WINDOW_SHOWN
    );
}

auto GUI::createRenderer(void) -> SDL_Renderer* {
    return SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

auto GUI::render(void) -> void {
    SDL_RenderPresent(renderer);
}

auto GUI::pumpEvents(void) -> void {
    SDL_PumpEvents();
}

auto GUI::drawPixel(int x, int y, int red, int green, int blue) -> void {
    auto r = SDL_Rect{};
    r.x = x * PIXEL_SIZE;
    r.y = y * PIXEL_SIZE;
    r.w = r.h = PIXEL_SIZE;

    SDL_SetRenderDrawColor(renderer, red, green, blue, 255);
    SDL_RenderFillRect(renderer, &r);
}

auto GUI::hasExit(void) -> bool {
    auto ev = SDL_Event{};
    return (SDL_PollEvent(&ev) != 0 && ev.type == SDL_QUIT) 
            || (isKeyPressed(SDL_SCANCODE_ESCAPE));
}

auto GUI::closeWindow(void) -> void {
    SDL_DestroyWindow(window);
}