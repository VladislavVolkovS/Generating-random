#include "sobol.h"

float sobol(uint32_t index, uint32_t base) {
    uint32_t result = 0;

    for(uint32_t j = base * sobol_matrices_size; index; index >>= 1, j++)
        if(index & 1)
            result ^= matrices[j];

    return result * (1.0 / static_cast<float>(1ULL << 32));
}

float sobol_scramble(uint32_t index, uint32_t base, uint32_t seed) {
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

    // for(uint32_t j = base * sobol_matrices_size; index; index >>= 1, j++)
    //     if(index & 1)
    //         result ^= matrices[j];

    // result = fast_owen_scramble(base, result);

    // result = nested_uniform_scramble()

    // return result * (1.0 / static_cast<float>(1ULL << 32));
}