cmake_minimum_required(VERSION 3.20)
project(peterson_mutex)

set(CMAKE_CXX_STANDARD 20)

set(PM_ADDRESS_SANITIZER OFF CACHE BOOL "Build with address sanitizer")
set(PM_BUILD_TEST OFF CACHE BOOL "Build library test")

# Build with address sanitizer
if(PM_ADDRESS_SANITIZER)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -static-libasan")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libasan")
endif()

add_subdirectory(peterson_mutex)

if(PM_BUILD_TEST)
    add_subdirectory(test)
endif()
