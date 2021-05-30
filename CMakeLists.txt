cmake_minimum_required(VERSION 3.0.0)
project(chip8 VERSION 0.1.0)

include(CTest)
enable_testing()

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(
    chip8 main.cpp 
    src/Memory/Memory.cpp src/Memory/Memory.hpp
    src/Emulator/Emulator.cpp src/Emulator/Emulator.hpp
    src/Display/Display.cpp src/Display/Display.hpp
    src/Fonts/Fonts.hpp
    src/DecodedInstruction/DecodedInstruction.hpp
    src/Keyboard/Keyboard.hpp
    src/GUI/GUI.cpp src/GUI/GUI.hpp
    src/OPCodes/OPCodes.h
    src/Parser/Parser.cpp src/Parser/Parser.hpp
)
target_link_libraries(chip8 ${SDL2_LIBRARIES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
