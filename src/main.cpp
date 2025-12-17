#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include "Config.hpp"

void mouse_button_callback(GLFWwindow*, int, int, int);
void processInput(GLFWwindow *, float *, float *, float *);

int main(int argc, char const *argv[])
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    float r = 0.0f, g = 0.0f, b = 0.0f;
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow *window = glfwCreateWindow(Config::WINDOW_HEIGHT, Config::WINDOW_WIDTH, Config::WINDOW_TITLE, NULL, NULL);
    
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, Config::WINDOW_HEIGHT, Config::WINDOW_WIDTH);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window, &r, &g, &b);
        glClearColor(r, g, b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    return 0;
}

void processInput(GLFWwindow *window, float *r, float *g, float *b)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
        *r = std::fmod(*r + 0.001f, 1.0f);
    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
        *g = std::fmod(*g + 0.001f, 1.0f);
    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
        *b = std::fmod(*b + 0.001f, 1.0f);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
    {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        
        std::cout << "Mouse position: " << xpos << ", " << ypos << std::endl;
    }
}