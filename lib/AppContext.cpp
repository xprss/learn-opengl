#include "AppContext.hpp"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <nlohmann/json.hpp>

AppContext::AppContext()
{
    for (size_t i = 0; i < color_palette.size(); ++i)
    {
        color_palette[i] = ColorEntity(Config::CLEAR_R, Config::CLEAR_G, Config::CLEAR_B, Config::CLEAR_ALPHA);
        current_color_palette_entity = &color_palette[0];
    }
}

AppContext &AppContext::get()
{
    static AppContext instance;
    return instance;
}

void AppContext::increment_color(float dr, float dg, float db)
{
    this->current_color_palette_entity->setRed(std::fmod(this->current_color_palette_entity->getRed() + dr, 1.0f));
    this->current_color_palette_entity->setGreen(std::fmod(this->current_color_palette_entity->getGreen() + dg, 1.0f));
    this->current_color_palette_entity->setBlue(std::fmod(this->current_color_palette_entity->getBlue() + db, 1.0f));
}

void AppContext::reset_color()
{
    this->current_color_palette_entity->setRed(Config::CLEAR_R);
    this->current_color_palette_entity->setGreen(Config::CLEAR_G);
    this->current_color_palette_entity->setBlue(Config::CLEAR_B);
    this->current_color_palette_entity->setAlpha(Config::CLEAR_ALPHA);
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
    try
    {
        nlohmann::json j;
        for (size_t i = 0; i < Config::COLOR_PALETTE_SIZE; i++)
        {
            j[Config::JSON_SAVEFILE_COLOR_OBJ_KEY].push_back({{Config::JSON_SAVEFILE_COLOR_R_KEY, this->color_palette[i].getRed()},
                                                              {Config::JSON_SAVEFILE_COLOR_G_KEY, this->color_palette[i].getGreen()},
                                                              {Config::JSON_SAVEFILE_COLOR_B_KEY, this->color_palette[i].getBlue()},
                                                              {Config::JSON_SAVEFILE_COLOR_ALPHA_KEY, this->color_palette[i].getAlpha()}});
        }

        std::filesystem::path path = Config::CWD / filename;

        std::ofstream file(path);
        if (!file)
        {
            throw std::runtime_error(
                std::string("File open error: ") + filename);
        }

        file << j.dump(4);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return false;
    }

    return true;
}

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

        nlohmann::json loaded_colors = j[Config::JSON_SAVEFILE_COLOR_OBJ_KEY];

        if (loaded_colors.size() != Config::COLOR_PALETTE_SIZE)
        {
            throw std::runtime_error("Invalid JSON: incorrect number of colors, will start from default");
        }

        for (size_t i = 0; i < Config::COLOR_PALETTE_SIZE; i++)
        {
            this->color_palette[i].setRed(loaded_colors[i].value(Config::JSON_SAVEFILE_COLOR_R_KEY, Config::CLEAR_R));
            this->color_palette[i].setGreen(loaded_colors[i].value(Config::JSON_SAVEFILE_COLOR_G_KEY, Config::CLEAR_G));
            this->color_palette[i].setBlue(loaded_colors[i].value(Config::JSON_SAVEFILE_COLOR_B_KEY, Config::CLEAR_B));
            this->color_palette[i].setAlpha(loaded_colors[i].value(Config::JSON_SAVEFILE_COLOR_ALPHA_KEY, Config::CLEAR_ALPHA));
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        this->current_color_palette_entity->setRed(Config::CLEAR_R);
        this->current_color_palette_entity->setGreen(Config::CLEAR_G);
        this->current_color_palette_entity->setBlue(Config::CLEAR_B);
        this->current_color_palette_entity->setAlpha(Config::CLEAR_ALPHA);
        return false;
    }

    return true;
}
