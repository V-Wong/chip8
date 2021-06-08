#include <iostream>
#include <iterator>
#include <vector>

#include "SDL.h"

#include "src/Emulator/Emulator.hpp"
#include "src/Display/Display.hpp"
#include "src/Keyboard/Keyboard.hpp"
#include "src/GUI/GUI.hpp"
#include "src/Parser/Parser.hpp"


int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s <rom>\n", argv[0]);
        exit(1);
    }

    auto e = Emulator(Parser::readProgram(argv[1]));
    auto gui = GUI();

    while (true) {
        gui.pumpEvents();
        if (gui.hasExit()) break;

        for (auto key : keyMap) {
            if (gui.isKeyPressed(key.first)) e.keyPress(key.second);
            else e.keyUnpress(key.second);
        }

        if (e.isDisplayUpdated()) {
            for (auto i = 0; i < DisplaySpecs::PIXEL_WIDTH; i++) {
                for (auto j = 0; j < DisplaySpecs::PIXEL_HEIGHT; j++) {
                    if (e.getPixel(i, j)) 
                        gui.drawPixel(i, j, 0, 0, 255);
                    else
                        gui.drawPixel(i, j, 0, 0, 0);
                }
            }
            gui.render();
        }

        e.run();
    }

    gui.closeWindow();
}
