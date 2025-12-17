cmake_minimum_required(VERSION 3.16)
project(learn_opengl LANGUAGES C CXX)

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
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(learn_opengl src/main.cpp)

target_include_directories(learn_opengl
    PRIVATE
    include
)

target_link_libraries(learn_opengl
    PRIVATE
    OpenGL::GL
    glfw
    glad
    appcontext
)
