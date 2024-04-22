#include "mitchels_bn.h"

inline static float PointDistance2D(Point lhs, Point rhs) {

    float x_delta = lhs.x - rhs.x;
    float y_delta = lhs.y - rhs.y;

    if (x_delta > 0.5f) {
        x_delta = 1 - x_delta;
    }
    if (y_delta > 0.5f) {
        y_delta = 1 - y_delta;
    }

    return std::sqrt(x_delta * x_delta + y_delta * y_delta);
}

inline static float PointDistance1D(float lhs, float rhs) {

    float x_delta = lhs - rhs;
    float y_delta = lhs - rhs;

    if (x_delta > 0.5f) {
        x_delta = 1 - x_delta;
    }
    if (y_delta > 0.5f) {
        y_delta = 1 - y_delta;
    }

    return std::sqrt(x_delta * x_delta + y_delta * y_delta);
}

void BlueNoiseGenerate2D(std::vector<Point>& BlueNoisePoints, uint32_t spp) {

    uint32_t samples_number = spp * spp;
    BlueNoisePoints.resize(samples_number);
    uint32_t seed = 11;
    uint32_t base = 3;

    std::mt19937 rng(seed);
    std::uniform_real_distribution<float> distribution(0, 1);

    BlueNoisePoints[0] = {distribution(rng), distribution(rng)}; // first point

    std::cout << "\n";
    for (size_t sample = 1; sample < samples_number; ++sample) {
        std::cout << sample << "\n";
        Point best_point;
        float max_distance = -1;

        for (size_t current_test = 0; current_test < base * sample; ++current_test) {

            Point test_point({distribution(rng), distribution(rng)});
            float distance = 3;

            for (size_t index = 0; index < sample; ++index) {
                distance = std::min(distance, PointDistance2D(BlueNoisePoints[index], test_point));
            }

            if (distance > max_distance) {
                max_distance = distance;
                best_point = test_point;
            }
        }

        BlueNoisePoints[sample] = best_point;

    }
}

void BlueNoiseGenerate1D(std::vector<float>& BlueNoisePoints, uint32_t spp) {

    uint32_t samples_number = spp * spp;
    BlueNoisePoints.resize(samples_number);
    uint32_t seed = 11;
    uint32_t base = 3;

    std::mt19937 rng(seed);
    std::uniform_real_distribution<float> distribution(0, 1);

    BlueNoisePoints[0] = {distribution(rng)}; // first point

    std::cout << "\n";
    for (size_t sample = 1; sample < samples_number; ++sample) {
        std::cout << sample << "\n";
        float best_point;
        float max_distance = -1;

        for (size_t current_test = 0; current_test < base * sample; ++current_test) {

            float test_point{distribution(rng)};
            float distance = 3;

            for (size_t index = 0; index < sample; ++index) {
                distance = std::min(distance, PointDistance1D(BlueNoisePoints[index], test_point));
            }

            if (distance > max_distance) {
                max_distance = distance;
                best_point = test_point;
            }
        }

        BlueNoisePoints[sample] = best_point;
    }
}