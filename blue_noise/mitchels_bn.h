#pragma once
#include <cmath>
#include <vector>
#include <random>
#include <iostream>

struct Point {
    float x = 0, y = 0;
};

void BlueNoiseGenerate(std::vector<Point>& BlueNoisePoints, uint32_t spp);