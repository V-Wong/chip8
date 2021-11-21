#include "Display.hpp"

auto Display::set(uint8_t x, uint8_t y) -> void {
    pixels.at(x).at(y) = true;
}

auto Display::unset(uint8_t x, uint8_t y) -> void {
    pixels.at(x).at(y) = false;
}

auto Display::flip(uint8_t x, uint8_t y) -> void {
    pixels.at(x).at(y) = !pixels.at(x).at(y);
}

auto Display::getPixel(uint8_t x, uint8_t y) -> bool {
    return pixels.at(x).at(y);
}