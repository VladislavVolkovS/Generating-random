#include "scramble.h"

uint32_t ReverseBits(uint32_t value) {

    value = (value << 16) | (value >> 16);
    value = ((value & 0x00ff00ff) << 8) | ((value & 0xff00ff00) >> 8);
    value = ((value & 0x0f0f0f0f) << 4) | ((value & 0xf0f0f0f0) >> 4);
    value = ((value & 0x33333333) << 2) | ((value & 0xcccccccc) >> 2);
    value = ((value & 0x55555555) << 1) | ((value & 0xaaaaaaaa) >> 1);
    return value;
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