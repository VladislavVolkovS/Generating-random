#pragma once

#include <iostream>
#include <vector>
#include "../scrambling/scramble.h"

uint32_t sobol_uint(uint32_t index, uint32_t dim);

float sobol(uint32_t index, uint32_t dim);

float sobol4d(uint32_t index, uint32_t dim, uint32_t seed);

float sobol_scramble(uint32_t index, uint32_t dim, uint32_t seed);