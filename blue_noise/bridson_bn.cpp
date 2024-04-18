#include "bridson_bn.h"

void SavePointToGrid(std::vector<std::optional<vec2>>& grid, float cell_size, int32_t grid_cols,
                     int32_t grid_rows, const vec2& point) {
    auto col = std::min(static_cast<int32_t>(point[0] / cell_size), grid_cols - 1);
    auto row = std::min(static_cast<int32_t>(point[1] / cell_size), grid_rows - 1);
    grid[col + row * grid_cols] = point;
}

float SquaredDistance(const vec2& point1, const vec2& point2) {
    return (point1[0] - point2[0]) * (point1[0] - point2[0]) +
           (point1[1] - point2[1]) * (point1[1] - point2[1]);
}



bool IsValidPoint(BlueNoiseData* data, const vec2& point, std::vector<std::optional<vec2>>& grid,
                  const float cell_size, const int32_t grid_cols, const int32_t grid_rows,
                  const float min_dist) {
        if (point[0] < 0 || point[0] >= data->width || point[1] < 0 || point[1] >= data->height) {
            return false;
        }

        auto col = std::min(static_cast<int32_t>(point[0] / cell_size), grid_cols - 1);
        auto row = std::min(static_cast<int32_t>(point[1] / cell_size), grid_rows - 1);

        if (grid[row * grid_cols + col].has_value()) {
            return false;
        }

        int32_t start_x = std::max(col - 2, 0);
        int32_t end_x = std::min(col + 2, grid_cols - 1);
        int32_t start_y = std::max(row - 2, 0);
        int32_t end_y = std::min(row + 2, grid_rows - 1);

        for (auto i = start_y; i <= end_y; ++i) {
            for (auto j = start_x; j <= end_x; ++j) {
                const auto& cell = grid[i * grid_cols + j];
                if (cell.has_value() && SquaredDistance(cell.value(), point) < min_dist) {
                    return false;
                }
            }
        }

        return true;
}

void BlueNoise(BlueNoiseData* data) {

    // clear previous data
    data->points.clear();

    std::random_device rd;
    std::mt19937 rng(rd());

    const auto cell_size = data->radius / std::sqrt(static_cast<float>(data->dimensions));
    const auto grid_cols = static_cast<int32_t>(std::ceil(data->width / cell_size));
    const auto grid_rows = static_cast<int32_t>(std::ceil(data->height / cell_size));
    const auto squared_min_dist = data->radius * data->radius - __FLT_EPSILON__;

    data->points.reserve(grid_cols * grid_rows);

    std::vector<std::optional<vec2>> grid(grid_cols * grid_rows);

    std::uniform_real_distribution<float> distrib;

    std::vector<vec2> active;

    vec2 start_point{data->width / 2.0f, data->height / 2.0f};

    SavePointToGrid(grid, cell_size, grid_cols, grid_rows, start_point);
    active.push_back(start_point);
    data->points.push_back(start_point);

    while (!active.empty()) {
        auto point = active.back();
        active.pop_back();

        for (uint32_t i = 0; i < data->n_looked_points; ++i) {
            auto radius = data->radius * std::sqrt(distrib(rng) * 3.0f + 1.0f);
            float angle_radians = 2.0f * PI * distrib(rng);
            vec2 current_point{point[0] + radius * std::cos(angle_radians),
                               point[1] + radius * std::sin(angle_radians)};
            if (!IsValidPoint(data, current_point, grid, cell_size, grid_cols, grid_rows,
                              squared_min_dist)) {
                continue;
            }
            SavePointToGrid(grid, cell_size, grid_cols, grid_rows, current_point);
            active.push_back(current_point);
            data->points.push_back(current_point);
        }
    }
}