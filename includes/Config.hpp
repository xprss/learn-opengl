#pragma once
#include <filesystem>

namespace Config
{
    // Window sizes
    constexpr int WINDOW_WIDTH = 800;
    constexpr int WINDOW_HEIGHT = 600;

    // Window title
    constexpr char WINDOW_TITLE[] = "xprss learning OpenGL";

    // Initial colors
    constexpr float CLEAR_R = 0.0f;
    constexpr float CLEAR_G = 0.0f;
    constexpr float CLEAR_B = 0.0f;
    constexpr float CLEAR_ALPHA = 1.0f;

    // Color and alpha indexes
    constexpr int COLOR_R_INDEX = 0;
    constexpr int COLOR_G_INDEX = 1;
    constexpr int COLOR_B_INDEX = 2;
    constexpr int COLOR_ALPHA_INDEX = 3;

    inline const std::filesystem::path CWD = std::filesystem::path(std::getenv("HOME")) / "code/learn-opengl/build";
}
