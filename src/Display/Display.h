#ifndef CHIP8_DISPLAY_H
#define CHIP8_DISPLAY_H

#include <memory>
#include <vector>
#include "SDL.h"

namespace DisplaySpecs {
    constexpr int PIXEL_WIDTH = 64;
    constexpr int PIXEL_HEIGHT = 32;
}


class Display {
public:
    Display(): pixels(
        DisplaySpecs::PIXEL_WIDTH, 
        std::vector<bool>(DisplaySpecs::PIXEL_HEIGHT)
    ) {};
    void set(int x, int y);
    void unset(int x, int y);
    void flip(int x, int y);
    bool getPixel(int x, int y);
private:
    std::vector<std::vector<bool>> pixels;
};


#endif //CHIP8_DISPLAY_H
