cmake_minimum_required(VERSION 3.0.0)
project(chip8 VERSION 0.1.0)

include(CTest)
enable_testing()

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(
    chip8 main.cpp 
    src/Memory/Memory.cpp src/Memory/Memory.h 
    src/Stack/Stack.cpp src/Stack/Stack.h 
    src/Emulator/Emulator.cpp src/Emulator/Emulator.h 
    src/Display/Display.cpp src/Display/Display.h
    src/Fonts/Fonts.h 
    src/DecodedInstruction/DecodedInstruction.h
    src/Keyboard/Keyboard.h
    src/GUI/GUI.cpp src/GUI/GUI.h
    src/Parser/Parser.cpp src/Parser/Parser.h
)
target_link_libraries(chip8 ${SDL2_LIBRARIES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
