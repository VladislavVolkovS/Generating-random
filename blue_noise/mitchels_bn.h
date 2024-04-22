#pragma once
#include <cmath>
#include <vector>
#include <random>
#include <iostream>

struct Point {
    float x = 0, y = 0;
};

void BlueNoiseGenerate1D(std::vector<float>& BlueNoisePoints, uint32_t spp);
void BlueNoiseGenerate2D(std::vector<Point>& BlueNoisePoints, uint32_t spp);