#pragma once

#include <iostream>
#include <vector>
#include "sbprimes.h"
#include "scramble.h"

double sobol(uint32_t index, uint32_t base);

double sobol_scramble(uint32_t index, uint32_t base);