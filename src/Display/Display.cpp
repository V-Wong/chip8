#include "Display.h"

void Display::draw(int x, int y) {
    pixels.at(x).at(y) = !pixels.at(x).at(y);
}
