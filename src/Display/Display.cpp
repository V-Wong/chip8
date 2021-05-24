#include "Display.h"

void Display::set(int x, int y) {
    pixels.at(x).at(y) = true;
}

void Display::unset(int x, int y) {
    pixels.at(x).at(y) = false;
}

void Display::flip(int x, int y) {
    pixels.at(x).at(y) = !pixels.at(x).at(y);
}

bool Display::getPixel(int x, int y) {
    return pixels.at(x).at(y);
}