cmake_minimum_required(VERSION 3.20)
project(transaction_memory)

file(GLOB_RECURSE TM_SRC "src/*.cpp")
add_library(${PROJECT_NAME} STATIC ${TM_SRC})

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC include
)
