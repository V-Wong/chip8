#pragma once

#include <map>
#include <SDL.h>


auto const keyMap = std::map<int, int>{
    {SDL_SCANCODE_1, 1}, {SDL_SCANCODE_2, 2}, {SDL_SCANCODE_3, 3}, {SDL_SCANCODE_4, 0xC},
    {SDL_SCANCODE_Q, 4}, {SDL_SCANCODE_W, 5}, {SDL_SCANCODE_E, 6}, {SDL_SCANCODE_R, 0xD},
    {SDL_SCANCODE_A, 7}, {SDL_SCANCODE_S, 8}, {SDL_SCANCODE_D, 9}, {SDL_SCANCODE_F, 0xE},
    {SDL_SCANCODE_Z, 0xA}, {SDL_SCANCODE_X, 0}, {SDL_SCANCODE_C, 0xB}, {SDL_SCANCODE_V, 0xF}
};
