#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <iostream>
#include <cmath>
#include <Config.hpp>
#include <AppContext.hpp>

void process_input();

int main(int argc, char const *argv[])
{
    AppContext &app = AppContext::get();

    app.init_window(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT, Config::WINDOW_TITLE);

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

    app.load_color_from_file(Config::COLOR_SAVEFILE);

    while (!glfwWindowShouldClose(app.window))
    {
        process_input();

        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::SetNextWindowPos(ImVec2(Config::WINDOW_WIDTH / 2.0f, Config::WINDOW_HEIGHT / 2.0f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
        ImGui::Begin("Color Adjuster", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::Text("Press R/G/B to increase Red/Green/Blue components");
        ImGui::ColorEdit4("Background Color", app.current_color_palette_entity->to_array().data());
        if (ImGui::Button("Reset Color"))
        {
            app.reset_color();
        }
        if (ImGui::IsItemHovered())
        {
            ImGui::SetTooltip("Restores the default background color.");
        }
        if (ImGui::Button("Save color to a file"))
        {
            try
            {
                app.store_color_to_file(Config::COLOR_SAVEFILE);
            }
            catch (const std::runtime_error &e)
            {
                std::cerr << "Error storing color to file: " << e.what() << std::endl;
            }
        }
        if (ImGui::IsItemHovered())
        {
            ImGui::SetTooltip("Stores the current background color parameters to a text file.");
        }
        if (ImGui::Button("Load color to a file"))
        {
            try
            {
                app.load_color_from_file(Config::COLOR_SAVEFILE);
            }
            catch (const std::runtime_error &e)
            {
                std::cerr << "Error loading color to file: " << e.what() << std::endl;
            }
        }
        if (ImGui::IsItemHovered())
        {
            ImGui::SetTooltip("Loads the current background color parameters to a text file.");
        }

        ImGui::End();

        ImGui::SetNextWindowPos(ImVec2(Config::WINDOW_WIDTH / 2.0f, 0.0f), ImGuiCond_Always, ImVec2(0.5f, -0.5f));
        ImGui::Begin("Instructions", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::Text("Use the following keys to adjust background color:");
        ImGui::BulletText("R: Increase Red");
        ImGui::BulletText("G: Increase Green");
        ImGui::BulletText("B: Increase Blue");
        ImGui::Text("Hold Shift while pressing R/G/B to decrease the respective color component.");
        ImGui::Text("Use Reset color button to restore default color.");
        ImGui::End();

        ImGui::SetNextWindowPos(ImVec2(Config::WINDOW_WIDTH / 2.0f, Config::WINDOW_HEIGHT * 2.0f / 3.0f), ImGuiCond_Always, ImVec2(0.5f, -0.5f));
        ImGui::Begin("Palette", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::ColorButton("Color 1", ImVec4(app.color_palette[0].red, app.color_palette[0].green, app.color_palette[0].blue, app.color_palette[0].alpha));
        ImGui::ColorButton("Color 2", ImVec4(app.color_palette[0].red, app.color_palette[0].green, app.color_palette[0].blue, app.color_palette[0].alpha));
        ImGui::ColorButton("Color 3", ImVec4(app.color_palette[0].red, app.color_palette[0].green, app.color_palette[0].blue, app.color_palette[0].alpha));
        ImGui::ColorButton("Color 4", ImVec4(app.color_palette[0].red, app.color_palette[0].green, app.color_palette[0].blue, app.color_palette[0].alpha));
        ImGui::ColorButton("Color 5", ImVec4(app.color_palette[0].red, app.color_palette[0].green, app.color_palette[0].blue, app.color_palette[0].alpha));
        ImGui::ColorButton("Color 6", ImVec4(app.color_palette[0].red, app.color_palette[0].green, app.color_palette[0].blue, app.color_palette[0].alpha));
        ImGui::ColorButton("Color 7", ImVec4(app.color_palette[0].red, app.color_palette[0].green, app.color_palette[0].blue, app.color_palette[0].alpha));
        ImGui::ColorButton("Color 8", ImVec4(app.color_palette[0].red, app.color_palette[0].green, app.color_palette[0].blue, app.color_palette[0].alpha));
        ImGui::ColorButton("Color 9", ImVec4(app.color_palette[0].red, app.color_palette[0].green, app.color_palette[0].blue, app.color_palette[0].alpha));
        ImGui::ColorButton("Color 10", ImVec4(app.color_palette[0].red, app.color_palette[0].green, app.color_palette[0].blue, app.color_palette[0].alpha));
        ImGui::End();

        app.reset_color();
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

    // delta variations for r, g, b
    float dr = 0.0f;
    float dg = 0.0f;
    float db = 0.0f;

    if (glfwGetKey(app.window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwGetKey(app.window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(app.window, true);
    }
    if (glfwGetKey(app.window, GLFW_KEY_R) == GLFW_PRESS)
    {
        if (!glfwGetKey(app.window, GLFW_KEY_LEFT_SHIFT) && !glfwGetKey(app.window, GLFW_KEY_RIGHT_SHIFT))
        {
            dr = 0.001f;
        }
        else
        {
            dr = -0.001f;
        }
    }
    if (glfwGetKey(app.window, GLFW_KEY_G) == GLFW_PRESS)
    {
        if (!glfwGetKey(app.window, GLFW_KEY_LEFT_SHIFT) && !glfwGetKey(app.window, GLFW_KEY_RIGHT_SHIFT))
        {
            dg = 0.001f;
        }
        else
        {
            dg = -0.001f;
        }
    }
    if (glfwGetKey(app.window, GLFW_KEY_B) == GLFW_PRESS)
    {
        if (!glfwGetKey(app.window, GLFW_KEY_LEFT_SHIFT) && !glfwGetKey(app.window, GLFW_KEY_RIGHT_SHIFT))
        {
            db = 0.001f;
        }
        else
        {
            db = -0.001f;
        }
    }
    app.increment_color(dr, dg, db);
}
