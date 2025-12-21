#pragma once
#include <GLFW/glfw3.h>
#include <cmath>

class AppContext
{
public:
    static AppContext &get();

    GLFWwindow *window = nullptr;
    float *colors4[4];
    float red, green, blue, alpha;

    void incrementColor(float dr, float dg, float db);
    void initWindow(int width, int height, const char *title);

private:
    AppContext();
    AppContext(const AppContext &) = delete;
    AppContext &operator=(const AppContext &) = delete;
};
