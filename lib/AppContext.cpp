#include "Config.hpp"
#include "AppContext.hpp"
#include <iostream>

AppContext::AppContext()
{
    this->r = Config::CLEAR_R;
    this->g = Config::CLEAR_G;
    this->b = Config::CLEAR_B;
}

AppContext &AppContext::get()
{
    static AppContext instance;
    return instance;
}

void AppContext::incrementColor(float dr, float dg, float db)
{
    r = std::fmod(r + dr, 1.0f);
    g = std::fmod(g + dg, 1.0f);
    b = std::fmod(b + db, 1.0f);
}

void AppContext::initWindow(int width, int height, const char *title)
{
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW\n";
        exit(-1);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // macOS
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    this->window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        exit(-1);
    }
}