#include "Display.hpp"

void Display::set(uint8_t x, uint8_t y) {
    pixels.at(x).at(y) = true;
}

void Display::unset(uint8_t x, uint8_t y) {
    pixels.at(x).at(y) = false;
}

void Display::flip(uint8_t x, uint8_t y) {
    pixels.at(x).at(y) = !pixels.at(x).at(y);
}

bool Display::getPixel(uint8_t x, uint8_t y) {
    return pixels.at(x).at(y);
}