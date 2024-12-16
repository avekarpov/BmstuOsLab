cmake_minimum_required(VERSION 3.20)
project(lab)

set(CMAKE_CXX_STANDARD 20)

set(LAB_ADDRESS_SANITIZER OFF CACHE BOOL "Build with address sanitizer")
set(LAB_BUILD_TEST OFF CACHE BOOL "Build library test")

# Build with address sanitizer
if(LAB_ADDRESS_SANITIZER)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -static-libasan")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libasan")
endif()

add_compile_options(-mavx)
add_compile_options(-mavx2)

add_subdirectory(peterson_mutex)
add_subdirectory(transaction_memory)
add_subdirectory(memory_functions)

if(LAB_BUILD_TEST)
    add_subdirectory(test)
endif()
