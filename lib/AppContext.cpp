#include "Config.hpp"
#include "AppContext.hpp"
#include <iostream>

AppContext::AppContext()
{
    this->red = Config::CLEAR_R;
    this->green = Config::CLEAR_G;
    this->blue = Config::CLEAR_B;
    this->alpha = Config::CLEAR_ALPHA;
    
    this->colors4[0] = &this->red;
    this->colors4[1] = &this->green;
    this->colors4[2] = &this->blue;
    this->colors4[3] = &this->alpha;
}

AppContext &AppContext::get()
{
    static AppContext instance;
    return instance;
}

void AppContext::incrementColor(float dr, float dg, float db)
{
    red = std::fmod(red + dr, 1.0f);
    green = std::fmod(green + dg, 1.0f);
    blue = std::fmod(blue + db, 1.0f);
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