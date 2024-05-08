#pragma once

#include <iostream>

uint32_t jenkinsHash(uint32_t x);

uint32_t initRNG(uint32_t pixelX, uint32_t pixelY, uint32_t width, uint32_t frame);

float uintToFloat(uint32_t x);

uint32_t xorshift(uint32_t &rngState);

float uniformRand(uint32_t &rngState);