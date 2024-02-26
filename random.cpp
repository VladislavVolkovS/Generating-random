#include "random.h"

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

float random(SamplerState& state, const SampleDimension dim, Generator gen_type, bool scrambling) {
    const uint32_t dimension = uint32_t(dim);
    const uint32_t base = Primes[dimension & 31u];
    if (gen_type == HALTON) {
        return scrambling ? halton_scramble(state.seed + state.sampleIdx, base)
                          : halton(state.seed + state.sampleIdx, base);
    } else if (gen_type == SOBOL) {
        return scrambling ? sobol_scramble(state.seed + state.sampleIdx, base, state.seed)
                          : sobol(state.seed + state.sampleIdx, base);
    } else {
        return GetRandomFromStd();
    }

}