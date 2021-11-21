#pragma once

#include <memory>
#include <vector>

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
    void set(uint8_t x, uint8_t y);
    void unset(uint8_t x, uint8_t y);
    void flip(uint8_t x, uint8_t y);
    bool getPixel(uint8_t x, uint8_t y);
private:
    std::vector<std::vector<bool>> pixels;
};
