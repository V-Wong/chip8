cmake_minimum_required(VERSION 3.0.0)
project(chip8 VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(
    chip8 main.cpp src/Memory/Memory.cpp src/Memory/Memory.h 
    src/Stack/Stack.cpp src/Stack/Stack.h src/Emulator/Emulator.cpp 
    src/Emulator/Emulator.h src/Display/Display.cpp src/Display/Display.h
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
