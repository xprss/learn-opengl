#include "Config.hpp"
#include "AppContext.hpp"
#include <iostream>

AppContext::AppContext()
{
}

AppContext &AppContext::get()
{
    static AppContext instance;
    return instance;
}

void AppContext::incrementColor(float dr, float dg, float db)
{
    this->colors4[Config::COLOR_R_INDEX] = std::fmod(this->colors4[Config::COLOR_R_INDEX] + dr, 1.0f);
    this->colors4[Config::COLOR_G_INDEX] = std::fmod(this->colors4[Config::COLOR_G_INDEX] + dg, 1.0f);
    this->colors4[Config::COLOR_B_INDEX] = std::fmod(this->colors4[Config::COLOR_B_INDEX] + db, 1.0f);
}

void AppContext::resetColor()
{
    this->colors4[Config::COLOR_R_INDEX] = Config::CLEAR_R;
    this->colors4[Config::COLOR_G_INDEX] = Config::CLEAR_G;
    this->colors4[Config::COLOR_B_INDEX] = Config::CLEAR_B;
    this->colors4[Config::COLOR_ALPHA_INDEX] = Config::CLEAR_ALPHA;
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