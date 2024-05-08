#pragma once

#include "sampler.h"
#include "halton/halton.h"
#include "sobol/sobol.h"
#include "blue_noise/mitchels_bn.h"
#include "uniform/uniform.h"
#include <random>

enum Generator {
    STL, HALTON, SOBOL, BLUE_NOISE, UNIFORM
};

float GetRandomFromStd();
void createBlueNoiseBuffer(std::vector<float>& blue_noise);

float random(SamplerState& state, const SampleDimension dim, Generator gen_type = STL,
             bool scrambling = false, float* blueNoiseData = nullptr, uint32_t size_mask = 0);