#include <memory_functions.hpp>
#include <catch2/catch_all.hpp>

TEST_CASE("vectorized_memset fills memory with a value", "[vectorized_memset]") {
    size_t size = 128; 
    char *buffer = new char[size];
    
    vectorized_memset(buffer, size, 'A');
    
    for (size_t i = 0; i < size; ++i) {
        REQUIRE(buffer[i] == 'A');
    }
    delete[] buffer;
}

TEST_CASE("vectorized_memcpy copies memory", "[vectorized_memcpy]") {
    size_t size = 128;
    char *source = new char[size];
    char *dest = new char[size];
    
    std::memset(source, 'A', size);
    
    vectorized_memcpy(dest, source, size);
    
    for (size_t i = 0; i < size; ++i) {
        REQUIRE(dest[i] == 'A');
    }
    delete[] source;
    delete[] dest;
}

TEST_CASE("vectorized_calloc allocates and zeroes memory", "[vectorized_calloc]") {
    size_t num = 128;
    size_t size = sizeof(char);
    char *buffer = static_cast<char*>(vectorized_calloc(num, size));
    
    for (size_t i = 0; i < num; ++i) {
        REQUIRE(buffer[i] == 0);
    }
    free(buffer);
}

TEST_CASE("vectorized_memmove moves memory correctly", "[vectorized_memmove]") {
    size_t size = 128;
    char *buffer = new char[size];

    for (size_t i = 0; i < size; ++i) {
        buffer[i] = static_cast<char>(i);
    }
    
    vectorized_memmove(buffer + 50, buffer, 50);
    
    for (size_t i = 0; i < 50; ++i) {
        REQUIRE(buffer[50 + i] == static_cast<char>(i));
    }
    delete[] buffer;
}

TEST_CASE("vectorized_memcmp compares memory correctly", "[vectorized_memcmp]") {
    size_t size = 128;
    char *buffer1 = new char[size];
    char *buffer2 = new char[size];
    
    std::memset(buffer1, 'A', size);
    std::memset(buffer2, 'A', size);
    
    REQUIRE(vectorized_memcmp(buffer1, buffer2, size) == 0);
    
    buffer2[0] = 'B';
    REQUIRE(vectorized_memcmp(buffer1, buffer2, size) != 0);
    
    buffer1[0] = 'B';
    REQUIRE(vectorized_memcmp(buffer1, buffer2, size) == 0);

    delete[] buffer1;
    delete[] buffer2;
}
