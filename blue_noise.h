#pragma once
#include <vector>
#include <random>
#include <fstream>
#include <optional>
#include <array>
#include <climits>


#define PI 3.141592653589793238462643383279502884L

using vec2 = std::array<float, 2>;

struct BlueNoiseData {
    std::vector<vec2> points;
    float width = 1.0f;
    float height = 1.0f;
    float radius = 0.04f;
    int32_t n_looked_points = 30; // default
    int32_t dimensions = 2; // default
};

void SavePointToGrid(std::vector<std::optional<vec2>>& grid, float cell_size, int32_t grid_cols,
                     int32_t grid_rows, const vec2& point);

float SquaredDistance(const vec2& point1, const vec2& point2);

bool IsValidPoint(BlueNoiseData* data, const vec2& point, std::vector<std::optional<vec2>>& grid,
                  const float cell_size, const int32_t grid_cols, const int32_t grid_rows,
                  const float min_dist);

void BlueNoise(BlueNoiseData* data);
