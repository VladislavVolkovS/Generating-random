#pragma once

#include <iostream>

uint32_t ReverseBits(uint32_t value);

uint32_t fast_owen_scramble(uint32_t seed, uint32_t value);

uint32_t laine_karras_permutation(uint32_t x, uint32_t seed)
{
    x += seed;
    x ^= x * 0x6c50b47cu;
    x ^= x * 0xb82f1e52u;
    x ^= x * 0xc7afe638u;
    x ^= x * 0x8d22f6e6u;
    return x;
}

uint32_t nested_uniform_scramble(uint32_t x, uint32_t seed)
{
    x = ReverseBits(x);
    x = laine_karras_permutation(x, seed);
    x = ReverseBits(x);
    return x;
}