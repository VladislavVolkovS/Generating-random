#include "sobol.h"

uint32_t hash_combine(uint32_t seed, uint32_t v) {
  return seed ^ (v + (seed << 6) + (seed >> 2));
}

uint32_t sbl(uint32_t index, uint32_t base)
{
    if (base > 4){
        return 0;
    }
    uint32_t X = 0;
    for (int bit = 0; bit < 32; bit++) {
        int mask = (index >> bit) & 1;
        X ^= mask * matrices[base * bit];
    }
    return X;
}

float sobol(uint32_t index, uint32_t base) {
    uint32_t result = 0;

    for(uint32_t j = base * sobol_matrices_size; index; index >>= 1, j++)
        if(index & 1)
            result ^= matrices[j];

    return result * (1.0 / static_cast<float>(1ULL << 32));
}

float sobol_scramble_no_shuffle(uint32_t index, uint32_t base, uint32_t seed) {
    uint32_t result = 0;

    if (base == 0) {
        return ReverseBits(index);
    } else {
        uint32_t i = 0;
        while (index != 0) {
            uint32_t j = __builtin_ctz(index);
            result ^= matrices[base * (i + j)];
            i += j + 1;
            index <<= j;
            index <<= 1;
        }
    }

    result = ReverseBits(ReverseBitsOwen(result, seed));

    return static_cast<float>(result) * (1.0f / 4294967808.0f);
}

float sobol_scramble(uint32_t index, uint32_t base, uint32_t seed) {

    uint32_t result = 0;

    // result = fast_owen_scramble(base, result);

    result = nested_uniform_scramble(result, seed);

    result = nested_uniform_scramble(sbl(index, base), hash_combine(seed, base));

    return result * (1.0 / static_cast<float>(1UL << 32));
}

uint32_t sobol4d(uint32_t index, uint32_t dim) {
    uint32_t result = 0;
    for (int bit = 0; bit < 32; bit++) {
        int mask = (index >> bit) & 1;
        result ^= mask * matrices[(dim % 4) * bit];
    }
    return result;
}

float sobol_scramble_shuffled(uint32_t index, uint32_t base, uint32_t seed) {

    uint32_t result = 0;

    // result = fast_owen_scramble(base, result);

    result = nested_uniform_scramble(result, seed);

    result = nested_uniform_scramble(sobol4d(index, base), hash_combine(seed, base));

    return result * (1.0 / static_cast<float>(1UL << 32));
}