cmake_minimum_required(VERSION 3.10)

project(graphing VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_REQUIRED True)

# GLFW, Glad, GLM, SPDLOG
add_subdirectory(third_party/glfw-3.3.4)
add_subdirectory(third_party/glad)
add_subdirectory(third_party/glm)
add_subdirectory(third_party/spdlog)

# OpenGL
find_package(OpenGL REQUIRED)

file(GLOB_RECURSE MAIN_HEADER ./src/*.h)
file(GLOB_RECURSE MAIN_SOURCE ./src/*.cpp)

option(PLATFORM_WINDOWS "Compile for Windows" ON)

if (PLATFORM_WINDOWS)
    add_definitions(-DPLATFORM_WINDOWS)
endif()

include_directories(./src)
include_directories(./third_party/stbi_image)
add_executable(graphing ${MAIN_SOURCE} ${MAIN_HEADER})

# GLFW, Glad, GLM, SPDLOG
target_link_libraries(graphing glfw)
target_link_libraries(graphing glad)
target_link_libraries(graphing glm)
target_link_libraries(graphing spdlog)

# target_precompile_headers(graphing PUBLIC ./src/gamepch.h)

# OpenGL
if (OpenGL_FOUND)
    target_link_libraries(graphing OpenGL::GL)
endif()
