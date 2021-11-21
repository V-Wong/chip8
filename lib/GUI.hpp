#include "SDL2/SDL.h"


class GUI {
public:
    GUI() {
        SDL_Init(SDL_INIT_VIDEO);
        window = createWindow();
        renderer = createRenderer();
        keyboardState = SDL_GetKeyboardState(NULL);
    };
    
    auto render(void) -> void;
    auto pumpEvents(void) -> void;
    auto isKeyPressed(int scancode) -> uint8_t { return keyboardState[scancode]; };
    auto drawPixel(int x, int y, int r, int g, int b) -> void;

    auto hasExit(void) -> bool;
    auto closeWindow(void) -> void;
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    const uint8_t *keyboardState;

    auto createWindow(void) -> SDL_Window*;
    auto createRenderer(void) -> SDL_Renderer*;
};