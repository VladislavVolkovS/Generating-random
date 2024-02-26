#pragma once

#include <iostream>
#include <vector>
#include "sbprimes.h"
#include "scramble.h"

float sobol(uint32_t index, uint32_t base);

float sobol_scramble(uint32_t index, uint32_t base, uint32_t seed);