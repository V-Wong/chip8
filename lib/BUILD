cc_library(
    name = "Emulator",
    srcs = ["Emulator.cpp"],
    hdrs = ["Emulator.hpp"],
    visibility = ["//main:__pkg__"],
    deps = ["//lib:Memory", "//lib:Display", "//lib:DecodedInstruction", "//lib:Fonts", "//lib:OPCodes"]
)

cc_library(
    name = "Display",
    srcs = ["Display.cpp"],
    hdrs = ["Display.hpp"],
    visibility = ["//main:__pkg__"],
)

cc_library(
    name = "Keyboard",
    srcs = [],
    hdrs = ["Keyboard.hpp"],
    visibility = ["//main:__pkg__"],
)

cc_library(
    name = "GUI",
    srcs = ["GUI.cpp"],
    hdrs = ["GUI.hpp"],
    visibility = ["//main:__pkg__"],
    deps = ["//lib:Display"],
    linkopts = ["-lSDL2", "-lSDL2main"],
    copts = ["-I/usr/include/SDL2"],
)

cc_library(
    name = "Parser",
    srcs = ["Parser.cpp"],
    hdrs = ["Parser.hpp"],
    visibility = ["//main:__pkg__"],
)

cc_library(
    name = "DecodedInstruction",
    srcs = [],
    hdrs = ["DecodedInstruction.hpp"],
)

cc_library(
    name = "Memory",
    srcs = ["Memory.cpp"],
    hdrs = ["Memory.hpp"]
)

cc_library(
    name = "Fonts",
    srcs = [],
    hdrs = ["Fonts.hpp"]
)

cc_library(
    name = "OPCodes",
    srcs = [],
    hdrs = ["OPCodes.hpp"]
)