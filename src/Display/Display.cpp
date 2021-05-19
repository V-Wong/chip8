#include "Display.h"

void Display::draw(int x, int y) {
    pixels.at(x).at(y) = !pixels.at(x).at(y);
}

bool Display::getPixel(int x, int y) {
    return pixels.at(x).at(y);
}