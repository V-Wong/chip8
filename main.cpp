#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>

#include "SDL.h"

#include "src/Emulator/Emulator.h"
#include "src/Memory/Memory.h"
#include "src/Stack/Stack.h"
#include "src/Display/Display.h"
#include "src/Keyboard/Keyboard.h"
#include "src/GUI/GUI.h"

constexpr int PIXEL_SIZE = 20;

std::vector<uint8_t> readProgram();

int main(int, char **) {
    Emulator e(readProgram());
    GUI gui;

    while (true) {
        gui.pumpEvents();

        for (auto key : keyMap) {
            if (gui.isKeyPressed(key.first)) e.keyPress(key.second);
            else e.keyUnpress(key.second);
        }

        if (e.isDisplayUpdated()) {
            for (int i = 0; i < DisplaySpecs::PIXEL_WIDTH; i++) {
                for (int j = 0; j < DisplaySpecs::PIXEL_HEIGHT; j++) {
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
}

std::vector<uint8_t> readProgram() {
    std::ifstream input("./pong.rom", std::ios::binary);

    std::vector<uint8_t> bytes(
         (std::istreambuf_iterator<char>(input)),
         (std::istreambuf_iterator<char>())
    );

    input.close();

    return bytes;
}
