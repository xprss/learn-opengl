cmake_minimum_required(VERSION 3.16)
project(color_picker LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

add_library(glad STATIC
    external/glad/src/glad.c
)

target_include_directories(glad
    PUBLIC
    external/glad/include
)

add_library(appcontext
    lib/AppContext.cpp
)

target_include_directories(appcontext
    PUBLIC lib
)

target_link_libraries(appcontext
    PUBLIC
    glfw
)

target_include_directories(appcontext
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/includes
)

add_library(imgui
    external/imgui/imgui.cpp
    external/imgui/imgui_demo.cpp
    external/imgui/imgui_draw.cpp
    external/imgui/imgui_tables.cpp
    external/imgui/imgui_widgets.cpp
    external/imgui/backends/imgui_impl_glfw.cpp
    external/imgui/backends/imgui_impl_opengl3.cpp
)

target_include_directories(imgui
    PUBLIC
        external/imgui
        external/imgui/backends
)

target_link_libraries(imgui
    PUBLIC
        glfw
        OpenGL::GL
)


add_executable(color_picker MACOSX_BUNDLE src/main.cpp)

target_include_directories(color_picker
    PRIVATE
    includes
    lib
)

target_link_libraries(color_picker
    PRIVATE
    OpenGL::GL
    glfw
    glad
    appcontext
    imgui
)
