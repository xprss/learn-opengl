#include "Config.hpp"
#include "AppContext.hpp"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <nlohmann/json.hpp>

AppContext::AppContext()
{
}

AppContext &AppContext::get()
{
    static AppContext instance;
    return instance;
}

void AppContext::increment_color(float dr, float dg, float db)
{
    this->current_color_palette_entity->red = std::fmod(this->current_color_palette_entity->red + dr, 1.0f);
    this->current_color_palette_entity->green = std::fmod(this->current_color_palette_entity->green + dg, 1.0f);
    this->current_color_palette_entity->blue = std::fmod(this->current_color_palette_entity->blue + db, 1.0f);
}

void AppContext::reset_color()
{
    this->current_color_palette_entity->red = Config::CLEAR_R;
    this->current_color_palette_entity->green = Config::CLEAR_G;
    this->current_color_palette_entity->blue = Config::CLEAR_B;
    this->current_color_palette_entity->alpha = Config::CLEAR_ALPHA;
}

void AppContext::init_window(int width, int height, const char *title)
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

bool AppContext::store_color_to_file(const std::string filename)
{
    nlohmann::json j;
    j["color"] = {
        {"R", this->current_color_palette_entity->red},
        {"G", this->current_color_palette_entity->green},
        {"B", this->current_color_palette_entity->blue},
        {"A", this->current_color_palette_entity->alpha}};

    std::filesystem::path path = Config::CWD / filename;

    std::ofstream file(path);
    if (!file)
    {
        throw std::runtime_error(
            std::string("File open error: ") + filename);
    }

    file << j.dump(4);

    return true;
}

bool AppContext::load_color_from_file(const std::string filename)
{
    std::filesystem::path path = Config::CWD / filename;

    std::ifstream file(path);
    if (!file)
    {
        throw std::runtime_error("File open error: " + path.string());
    }

    nlohmann::json j;
    file >> j;

    if (!j.contains("color"))
    {
        throw std::runtime_error("Invalid JSON: missing 'color'");
    }

    nlohmann::json color = j["color"];

    this->current_color_palette_entity->red = color.value("r", Config::CLEAR_R);
    this->current_color_palette_entity->green = color.value("g", Config::CLEAR_G);
    this->current_color_palette_entity->blue = color.value("b", Config::CLEAR_B);
    this->current_color_palette_entity->alpha = color.value("a", Config::CLEAR_ALPHA);

    return true;
}
