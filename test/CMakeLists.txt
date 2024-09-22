cmake_minimum_required(VERSION 3.20)
project(test_peterson_mutex)

add_subdirectory(libs)

file(GLOB_RECURSE PM_TEST_SRC "src/*.cpp")
add_executable(${PROJECT_NAME} ${PM_TEST_SRC})

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC include
)

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE 
        Catch2::Catch2WithMain
        peterson_mutex
)
