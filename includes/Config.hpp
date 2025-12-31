#pragma once
#include <filesystem>

namespace Config
{
    // Window sizes
    constexpr int WINDOW_WIDTH = 800;
    constexpr int WINDOW_HEIGHT = 600;

    // Window title
    constexpr char WINDOW_TITLE[] = "A fantastic palette of colors";

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

    // JSON savefile keys
    constexpr const char* JSON_SAVEFILE_COLOR_OBJ_KEY = "color";
    constexpr const char* JSON_SAVEFILE_COLOR_R_KEY = "R";
    constexpr const char* JSON_SAVEFILE_COLOR_G_KEY = "G";
    constexpr const char* JSON_SAVEFILE_COLOR_B_KEY = "B";
    constexpr const char* JSON_SAVEFILE_COLOR_ALPHA_KEY = "A";

    // background color savefile name
    const std::string COLOR_SAVEFILE = "background_color.txt";

    // Current working directory
    inline const std::filesystem::path CWD = std::filesystem::path(std::getenv("HOME")) / "code/learn-opengl/build";
}
