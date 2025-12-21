#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <iostream>
#include <cmath>
#include <Config.hpp>
#include <AppContext.hpp>

void mouse_button_callback(GLFWwindow *, int, int, int);
void process_input();

int main(int argc, char const *argv[])
{
    AppContext &app = AppContext::get();

    app.initWindow(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT, Config::WINDOW_TITLE);

    // glfwSetMouseButtonCallback(app.window, mouse_button_callback);

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

    glViewport(0, 0, Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
    // io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(app.window, true); // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
    ImGui_ImplOpenGL3_Init();

    while (!glfwWindowShouldClose(app.window))
    {
        process_input();

        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Color Adjuster");
        ImGui::Text("Press R/G/B to increase Red/Green/Blue components");
        ImGui::ColorEdit4("Background Color", *app.colors4);
        glClearColor(app.red, app.green, app.blue, app.alpha);
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(app.window);
        glClear(GL_COLOR_BUFFER_BIT);
    }
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    return 0;
}

void process_input()
{
    AppContext &app = AppContext::get();
    if (glfwGetKey(app.window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwGetKey(app.window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(app.window, true);
    }
    if (glfwGetKey(app.window, GLFW_KEY_R) == GLFW_PRESS)
    {
        if (!glfwGetKey(app.window, GLFW_KEY_LEFT_SHIFT) && !glfwGetKey(app.window, GLFW_KEY_RIGHT_SHIFT))
        {
            app.red = std::fmod(app.red + 0.001f, 1.0f);
        }
        else
        {
            app.red = std::fmod(app.red - 0.001f, 1.0f);
        }
    }
    if (glfwGetKey(app.window, GLFW_KEY_G) == GLFW_PRESS)
    {
        if (!glfwGetKey(app.window, GLFW_KEY_LEFT_SHIFT) && !glfwGetKey(app.window, GLFW_KEY_RIGHT_SHIFT))
        {
            app.green = std::fmod(app.green + 0.001f, 1.0f);
        }
        else
        {
            app.green = std::fmod(app.green - 0.001f, 1.0f);
        }
    }
    if (glfwGetKey(app.window, GLFW_KEY_B) == GLFW_PRESS)
    {
        if (!glfwGetKey(app.window, GLFW_KEY_LEFT_SHIFT) && !glfwGetKey(app.window, GLFW_KEY_RIGHT_SHIFT))
        {
            app.blue = std::fmod(app.blue + 0.001f, 1.0f);
        }
        else
        {
            app.blue = std::fmod(app.blue - 0.001f, 1.0f);
        }
    }
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
