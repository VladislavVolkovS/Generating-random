#include "halton.h"

float halton(int index, int base) {
    int d;
    int j;
    float prime_inv = 1.0f / static_cast<float>(base);
    float result = 0.0f;
    int t = index;

    while (t > 0) {
        d = (t % base);
        result += static_cast<float>(d) * prime_inv;
        prime_inv = prime_inv / static_cast<float>(base);
        t = (t - d) / base;
    }
    return result;
}

float halton_scramble(int index, int base) {
    int d;
    int j;
    float prime_inv = 1.0f / static_cast<float>(base);
    float result = 0.0f;
    int t = index;

    while (t > 0) {
        d = (t % base);
        result += static_cast<float>(d) * prime_inv;
        prime_inv = prime_inv / static_cast<float>(base);
        t = (t - d) / base;
    }
    return result;
}