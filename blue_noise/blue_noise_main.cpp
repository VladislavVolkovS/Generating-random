#include "bridson_bn.h"
#include "mitchels_bn.h"
#include "fstream"
#include <iostream>

int main() {
    // Bridson
    std::ofstream file;
    file.open("bridson_bn.csv");
    BlueNoiseData data{};
    data.radius = 0.05f;
    data.n_looked_points = 100;
    BlueNoise(&data);
    for (const auto& point : data.points) {
        file << point[0] << "," << point[1] << "\n";
    }
    file.close();

    // Mitchel's Best Candidate
    file.open("mitchels_bn_2D_16x16.csv");
    std::vector<Point> points_2D;
    BlueNoiseGenerate2D(points_2D, 16);
    for (const auto& point : points_2D) {
        file << point.x << "," << point.y << "\n";
        // std::cout << point.x << ", ";
    }
    file.close();
    // Mitchel's Best Candidate
    file.open("mitchels_bn_1D_32x32.csv");
    std::vector<float> points_1D;
    BlueNoiseGenerate1D(points_1D, 32);
    for (const auto& point : points_1D) {
        file << point << "," << "\n";
        // std::cout << point << ", ";
    }
    file.close();
    return 0;
}