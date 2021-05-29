#ifndef CHIP8_GUI_H
#define CHIP8_GUI_H

#include "SDL.h"


class GUI {
public:
    GUI() {
        SDL_Init(SDL_INIT_VIDEO);
        window = createWindow();
        renderer = createRenderer();
        keyboardState = SDL_GetKeyboardState(NULL);
    };
    
    void render(void);
    void pumpEvents(void);
    const uint8_t isKeyPressed(int scancode) { return keyboardState[scancode]; };
    void drawPixel(int x, int y, int r, int g, int b);

    bool hasExit(void);
    void closeWindow(void);
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    const uint8_t *keyboardState;

    SDL_Window* createWindow(void);
    SDL_Renderer* createRenderer(void);
};

#endif //CHIP8_GUI_H