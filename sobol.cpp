#include "sobol.h"

double sobol(uint32_t index, uint32_t base) {
    uint32_t result = 0;

    for(uint32_t j = base * sobol_matrices_size; index; index >>= 1, j++)
        if(index & 1)
            result ^= matrices[j];

    return result * (1.0 / static_cast<double>(1ULL << 32));
}

double sobol_scramble(uint32_t index, uint32_t base) {
    uint32_t result = 0;

    for(uint32_t j = base * sobol_matrices_size; index; index >>= 1, j++)
        if(index & 1)
            result ^= matrices[j];

    result = fast_owen_scramble(base, result);

    return result * (1.0 / static_cast<double>(1ULL << 32));
}