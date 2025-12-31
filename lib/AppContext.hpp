#pragma once
#include <GLFW/glfw3.h>
#include <cmath>
#include <array>
#include "Config.hpp"
#include "ColorEntity.hpp"

class AppContext
{
public:
    static AppContext &get();

    GLFWwindow *window = nullptr;
    std::array<ColorEntity, Config::COLOR_PALETTE_SIZE> color_palette;
    ColorEntity *current_color_palette_entity = nullptr;

    void init_window(int width, int height, const char *title);
    void increment_color(float dr, float dg, float db);
    void reset_color();
    bool store_color_to_file(const std::string filename);
    bool load_color_from_file(const std::string filename);

private:
    AppContext();
    AppContext(const AppContext &) = delete;
    AppContext &operator=(const AppContext &) = delete;
};
