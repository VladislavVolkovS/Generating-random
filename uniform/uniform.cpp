#include "uniform.h"

uint32_t jenkinsHash(uint32_t x) {
    x += x << 10;
    x ^= x >> 6;
    x += x << 3;
    x ^= x >> 11;
    x += x << 15;
    return x;
};

uint32_t initRNG(uint32_t pixelX, uint32_t pixelY, uint32_t width, uint32_t frame) {
    uint32_t dot = pixelX * 1 + pixelY * width;
    uint32_t rngState = dot ^ jenkinsHash(frame);
    return jenkinsHash(rngState);
};

float uintToFloat(uint32_t x) {
    #ifdef __CUDACC__
    return __uint_as_float((uint32_t)(0x3f800000 | (x >> 9))) - 1.f;
    #else
    union{
        uint32_t i;
        float f;
    };
    i = ((uint32_t)(0x3f800000 | (x >> 9)));
    return f - 1.f;
    #endif
};

uint32_t xorshift(uint32_t &rngState) {
    rngState ^= rngState << 13;
    rngState ^= rngState >> 17;
    rngState ^= rngState << 5;
    return rngState;
};

float uniformRand(uint32_t &rngState) {
    return uintToFloat(xorshift(rngState));
};