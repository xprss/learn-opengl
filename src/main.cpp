#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <iostream>
#include <cmath>
#include <includes/Config.hpp>
#include <AppContext.hpp>

void mouse_button_callback(GLFWwindow *, int, int, int);
void processInput();

int main(int argc, char const *argv[])
{
    AppContext &app = AppContext::get();

    app.initWindow(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT, Config::WINDOW_TITLE);
    glfwSetMouseButtonCallback(app.window, mouse_button_callback);

    if (app.window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(app.window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, Config::WINDOW_HEIGHT, Config::WINDOW_WIDTH);

    while (!glfwWindowShouldClose(app.window))
    {
        processInput();
        glClearColor(app.red, app.green, app.blue, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(app.window);
        glfwPollEvents();
    }
    return 0;
}

void processInput()
{
    AppContext &app = AppContext::get();
    if (glfwGetKey(app.window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwGetKey(app.window, GLFW_KEY_Q) == GLFW_PRESS)
        glfwSetWindowShouldClose(app.window, true);
    if (glfwGetKey(app.window, GLFW_KEY_R) == GLFW_PRESS)
        app.red = std::fmod(app.red + 0.001f, 1.0f);
    if (glfwGetKey(app.window, GLFW_KEY_G) == GLFW_PRESS)
        app.green = std::fmod(app.green + 0.001f, 1.0f);
    if (glfwGetKey(app.window, GLFW_KEY_B) == GLFW_PRESS)
        app.blue = std::fmod(app.blue + 0.001f, 1.0f);
}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
    {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        std::cout << "Mouse position: " << xpos << ", " << ypos << std::endl;
    }
}