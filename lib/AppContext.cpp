#include "Config.hpp"
#include "AppContext.hpp"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <nlohmann/json.hpp>
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
void AppContext::increment_color(float dr, float dg, float db)
{
    this->current_color_palette_entity->color[Config::COLOR_R_INDEX] = std::fmod(this->current_color_palette_entity->color[Config::COLOR_R_INDEX] + dr, 1.0f);
    this->current_color_palette_entity->color[Config::COLOR_G_INDEX] = std::fmod(this->current_color_palette_entity->color[Config::COLOR_G_INDEX] + dg, 1.0f);
    this->current_color_palette_entity->color[Config::COLOR_B_INDEX] = std::fmod(this->current_color_palette_entity->color[Config::COLOR_B_INDEX] + db, 1.0f);
}

void AppContext::reset_color()
void AppContext::reset_color()
{
    this->current_color_palette_entity->color[Config::COLOR_R_INDEX] = Config::CLEAR_R;
    this->current_color_palette_entity->color[Config::COLOR_G_INDEX] = Config::CLEAR_G;
    this->current_color_palette_entity->color[Config::COLOR_B_INDEX] = Config::CLEAR_B;
    this->current_color_palette_entity->color[Config::COLOR_ALPHA_INDEX] = Config::CLEAR_ALPHA;
}

void AppContext::init_window(int width, int height, const char *title)
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
bool AppContext::store_color_to_file(const std::string filename)
{
    nlohmann::json j;
    j[Config::JSON_SAVEFILE_COLOR_OBJ_KEY] = {
        {Config::JSON_SAVEFILE_COLOR_R_KEY, this->current_color_palette_entity->color[Config::COLOR_R_INDEX]},
        {Config::JSON_SAVEFILE_COLOR_G_KEY, this->current_color_palette_entity->color[Config::COLOR_G_INDEX]},
        {Config::JSON_SAVEFILE_COLOR_B_KEY, this->current_color_palette_entity->color[Config::COLOR_B_INDEX]},
        {Config::JSON_SAVEFILE_COLOR_ALPHA_KEY, this->current_color_palette_entity->color[Config::COLOR_ALPHA_INDEX]}};

    std::filesystem::path path = Config::CWD / filename;
    std::filesystem::path path = Config::CWD / filename;

    std::ofstream file(path);
    if (!file)
    {
        throw std::runtime_error(
            std::string("File open error: ") + filename);
    }

    file << j.dump(4);
    file << j.dump(4);

    return true;
}

bool AppContext::load_color_from_file(const std::string filename)
bool AppContext::load_color_from_file(const std::string filename)
{
    try
    {
        std::filesystem::path path = Config::CWD / filename;

        std::ifstream file(path);
        if (!file)
        {
            throw std::runtime_error("File open error: " + path.string());
        }

        nlohmann::json j;
        file >> j;

        if (!j.contains(Config::JSON_SAVEFILE_COLOR_OBJ_KEY))
        {
            throw std::runtime_error("Invalid JSON: missing 'color'");
        }

        nlohmann::json color = j[Config::JSON_SAVEFILE_COLOR_OBJ_KEY];

        this->current_color_palette_entity->color[Config::COLOR_R_INDEX] = color.value(Config::JSON_SAVEFILE_COLOR_R_KEY, Config::CLEAR_R);
        this->current_color_palette_entity->color[Config::COLOR_G_INDEX] = color.value(Config::JSON_SAVEFILE_COLOR_G_KEY, Config::CLEAR_G);
        this->current_color_palette_entity->color[Config::COLOR_B_INDEX] = color.value(Config::JSON_SAVEFILE_COLOR_B_KEY, Config::CLEAR_B);
        this->current_color_palette_entity->color[Config::COLOR_ALPHA_INDEX] = color.value(Config::JSON_SAVEFILE_COLOR_ALPHA_KEY, Config::CLEAR_ALPHA);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        this->current_color_palette_entity->color[Config::COLOR_R_INDEX] = Config::CLEAR_R;
        this->current_color_palette_entity->color[Config::COLOR_G_INDEX] = Config::CLEAR_G;
        this->current_color_palette_entity->color[Config::COLOR_B_INDEX] = Config::CLEAR_B;
        this->current_color_palette_entity->color[Config::COLOR_ALPHA_INDEX] = Config::CLEAR_ALPHA;
        return false;
    }

    return true;
}

