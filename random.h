#pragma once

#include "sampler.h"
#include "halton/halton.h"
#include "sobol/sobol.h"
#include "blue_noise/mitchels_bn.h"
#include <random>

enum Generator {
    STL, HALTON, SOBOL, BLUE_NOISE
};

float GetRandomFromStd();

float random(SamplerState& state, const SampleDimension dim, Generator gen_type = STL,
             bool scrambling = false);