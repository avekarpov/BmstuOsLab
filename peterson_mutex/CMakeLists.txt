cmake_minimum_required(VERSION 3.20)
project(peterson_mutex)

file(GLOB_RECURSE PM_SRC "src/*.cpp")
add_library(${PROJECT_NAME} STATIC ${PM_SRC})

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC include
)
