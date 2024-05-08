#include "random.h"
#include <fstream>

float GetRandomFromStd() {
	static std::default_random_engine generator;

	// static std::mt19937 generator; // std::mersenne_twister_engine<std::uint_fast32_t, 32, 624, 397, 31,
    //                         			 0x9908b0df, 11,
    //                         			 0xffffffff, 7,
    //                          		 0x9d2c5680, 15,
    //                         			 0xefc60000, 18, 1812433253>

	// static std::minstd_rand0 generator; // std::linear_congruential_engine<std::uint_fast32_t, 16807, 0, 2147483647>

	// static std::ranlux24_base generator; // std::subtract_with_carry_engine<std::uint_fast32_t, 24, 10, 24>

	// static std::ranlux48_base generator; // std::subtract_with_carry_engine<std::uint_fast64_t, 48, 5, 12>

	// static std::knuth_b generator; // std::shuffle_order_engine<std::minstd_rand0, 256>

	static std::uniform_real_distribution<float> distribution(0.0, 1.0);

	return distribution(generator);
}

void createBlueNoiseBuffer(std::vector<float>& blue_noise) {
    const uint32_t w = 256;
    const uint32_t h = 256;
    const uint32_t dim = 2;

    std::ifstream file("./bn.txt");

    float num;
    while (file >> num) {
        blue_noise.push_back(num);
    }
    file.close();
}

float random(SamplerState& state, const SampleDimension dim, Generator gen_type, bool scrambling,
             float* blueNoiseData, uint32_t size_mask) {
    const uint32_t dimension = uint32_t(dim);
    if (gen_type == HALTON) {
        const uint32_t base = Primes[dimension & 31u];
        return scrambling ? halton_scramble(state.sampleIdx + state.seed, base)
                          : halton(state.sampleIdx, base);
    } else if (gen_type == SOBOL) {
        return scrambling ? sobol_scramble(state.sampleIdx, dimension % 5, state.seed)
                          : sobol(state.sampleIdx, dimension % 5);
    } else if (gen_type == BLUE_NOISE) {
        if (dimension > 3) {
            return sobol_scramble(state.sampleIdx, dimension % 5, state.seed);
        }
        int offsetX = state.bn_offset;
        int offsetY = state.bn_offset;
        if (dimension > 1) {
            offsetX *= 7;
            offsetY *= 5;
        }
        offsetX *= 17;
        offsetY *= 13;
        const int bnRow = (state.pixelY + offsetX) % size_mask;
        const int bnCol = (state.pixelX + offsetY) % size_mask;
        const int bnLinearIndex = (bnRow * size_mask + bnCol) * 2 + (dimension % 2); // 2 floats per bn texel, we select 0 or 1 to fetch x or y value
        return blueNoiseData[bnLinearIndex];
    } else if (gen_type == UNIFORM) {
        for (int32_t i = 0; i < (int32_t)dimension - 1; ++i) {
            uniformRand(state.seed);
        }
        return uniformRand(state.seed);
    } else {
        return GetRandomFromStd();
    }

}