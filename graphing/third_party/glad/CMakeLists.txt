cmake_minimum_required(VERSION 3.0)

project(GLAD VERSION 3.3.4 LANGUAGES C)

set(glad_HEADERS include/glad/glad.h include/KHR/khrplatform.h)
set(glad_SOURCES src/glad.c)

add_library(glad ${glad_SOURCES} ${glad_HEADERS})

target_include_directories(glad PUBLIC include)