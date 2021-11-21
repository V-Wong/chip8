cc_binary(
    name = "main",
    srcs = ["main.cpp"],
    linkopts = ["-lSDL2", "-lSDL2main"],
    copts = ["-I/usr/include/SDL2"],
    deps = [
        "//lib:Emulator",
        "//lib:Display",
        "//lib:Keyboard",
        "//lib:GUI",
        "//lib:Parser",
    ],
)
