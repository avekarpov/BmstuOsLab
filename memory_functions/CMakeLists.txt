cmake_minimum_required(VERSION 3.20)
project(memory_functions)

file(GLOB_RECURSE MF_SRC "src/*.cpp")
add_library(${PROJECT_NAME} STATIC ${MF_SRC})

target_include_directories(
        ${PROJECT_NAME}
        PUBLIC include
)
