#pragma once

#include "sampler.h"
#include "halton.h"
#include "sobol.h"
#include <random>

enum Generator {
    STL, HALTON, SOBOL, BLUE_NOISE
};

float GetRandomFromStd();

float random(SamplerState& state, const SampleDimension dim, Generator gen_type = STL,
             bool scrambling = false);