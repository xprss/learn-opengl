#pragma once
#include <GLFW/glfw3.h>
#include <cmath>
#include <array>
#include "Config.hpp"

class AppContext
{
public:
    static AppContext &get();

    GLFWwindow *window = nullptr;
    std::array<float, 4> colors4{Config::CLEAR_R, Config::CLEAR_G, Config::CLEAR_B, Config::CLEAR_ALPHA};

    void incrementColor(float dr, float dg, float db);
    void initWindow(int width, int height, const char *title);

private:
    AppContext();
    AppContext(const AppContext &) = delete;
    AppContext &operator=(const AppContext &) = delete;
};
