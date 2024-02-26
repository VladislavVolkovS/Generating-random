#include "scramble.h"

uint32_t ReverseBits(uint32_t value) {

    value = (((value & 0xaaaaaaaa) >> 1) | ((value & 0x55555555) << 1));
    value = (((value & 0xcccccccc) >> 2) | ((value & 0x33333333) << 2));
    value = (((value & 0xf0f0f0f0) >> 4) | ((value & 0x0f0f0f0f) << 4));
    value = (((value & 0xff00ff00) >> 8) | ((value & 0x00ff00ff) << 8));
    return ((value >> 16) | (value << 16));

}

uint32_t ReverseBitsOwen(uint32_t value, uint32_t seed) {

    value ^= value * 0x3d20adea;
    value += seed;
    value *= (seed >> 16) | 1;
    value ^= value * 0x05526c56;
    value ^= value * 0x53a22864;

    return value;
}

uint32_t laine_karras_permutation(uint32_t x, uint32_t seed) {
    x += seed;
    x ^= x * 0x6c50b47cu;
    x ^= x * 0xb82f1e52u;
    x ^= x * 0xc7afe638u;
    x ^= x * 0x8d22f6e6u;
    return x;
}

uint32_t nested_uniform_scramble(uint32_t x, uint32_t seed) {
    x = ReverseBits(x);
    x = laine_karras_permutation(x, seed);
    x = ReverseBits(x);
    return x;
}

uint32_t fast_owen_scramble(uint32_t seed, uint32_t value) {
    value = ReverseBits(value);

    value ^= value * 0x3d20adea;
    value ^= (value >> 1) & (value << 1) & 0x55555555;
    value += seed;
    value *= (seed >> 16) | 1;
    value ^= (value >> 1) & (value << 1) & 0x55555555;
    value ^= value * 0x05526c56;
    value ^= value * 0x53a22864;

    value = ReverseBits(value);

    return value;
}