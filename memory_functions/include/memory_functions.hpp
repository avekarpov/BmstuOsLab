#pragma once

#include <immintrin.h>
#include <new>

template <class Value_t = char>
void vectorized_memset(void *ptr, size_t size, Value_t value = Value_t{}) {
    const size_t aligned_size = size / 32 * 32;
    const __m256i v = _mm256_set1_epi8(value);

    size_t i;
    for (i = 0; i < aligned_size; i += 32) {
        _mm256_storeu_si256(reinterpret_cast<__m256i *>(&static_cast<char *>(ptr)[i]), v);
    }
    for (i = aligned_size; i < size; ++i) {
        static_cast<char *>(ptr)[i] = value;
    }
}

inline void vectorized_memcpy(void *dest, const void *src, size_t size) {
    const size_t aligned_size = size / 32 * 32;

    size_t i;
    for (i = 0; i < aligned_size; i += 32) {
        const __m256i v = _mm256_loadu_si256(reinterpret_cast<__m256i *>(&const_cast<char *>(static_cast<const char*>(src))[i]));
        _mm256_storeu_si256(reinterpret_cast<__m256i *>(&static_cast<char *>(dest)[i]), v);
    }
    for (i = aligned_size; i < size; ++i) {
        static_cast<char *>(dest)[i] = static_cast<const char*>(src)[i];
    }
}

inline void *vectorized_calloc(size_t num, size_t size) {
    const auto total_size = num * size;

    auto ptr = static_cast<char *>(malloc(total_size));
    if (ptr == nullptr) {
        throw std::bad_alloc{};
    }

    const size_t aligned_size = total_size / 32 * 32;
    const __m256i zero = _mm256_setzero_si256();

    size_t i;
    for (i = 0; i < aligned_size; i += 32) {
        _mm256_storeu_si256(reinterpret_cast<__m256i *>(&ptr[i]), zero);
    }
    for (i = aligned_size; i < total_size; ++i) {
        ptr[i] = 0;
    }

    return ptr;
}

inline void vectorized_memmove(void *dest, const void *src, size_t size) {
    if (dest == src) {
        return;
    }

    char *d = static_cast<char*>(dest);
    const char *s = static_cast<const char*>(src);

    if (d < s || d >= s + size) {
        vectorized_memcpy(dest, src, size);
    }
    else {
        size_t i;
        for (i = size - 32; i >= 32; i -= 32) {
            __m256i v = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(&s[i]));
            _mm256_storeu_si256(reinterpret_cast<__m256i*>(&d[i]), v);
        }

        if (i > 0) {
            size_t remainder = size % 32;
            for (size_t j = 0; j < remainder; ++j) {
                d[i + j] = s[i + j];
            }
        }
    }
}

inline int vectorized_memcmp(const void *ptr1, const void *ptr2, size_t size) {
    auto p1 = static_cast<const char*>(ptr1);
    auto p2 = static_cast<const char*>(ptr2);

    size_t i = 0;
    size_t aligned_size = size / 32 * 32;

    for (i = 0; i < aligned_size; i += 32) {
        __m256i v1 = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(&p1[i]));
        __m256i v2 = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(&p2[i]));

        __m256i diff = _mm256_xor_si256(v1, v2);

        if (!_mm256_testz_si256(diff, diff)) {
            for (size_t j = 0; j < 32; ++j) {
                if (p1[i + j] != p2[i + j]) {
                    return (p1[i + j] < p2[i + j]) ? -1 : 1;
                }
            }
        }
    }

    for (i = aligned_size; i < size; ++i) {
        if (p1[i] != p2[i]) {
            return (p1[i] < p2[i]) ? -1 : 1;
        }
    }

    return 0;
}