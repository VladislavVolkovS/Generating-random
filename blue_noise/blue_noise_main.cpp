#include "bridson_bn.h"
#include "mitchels_bn.h"
#include "fstream"

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
    file.open("mitchels_bn.csv");
    std::vector<Point> points;
    BlueNoiseGenerate(points, 32);
    for (const auto& point : points) {
        file << point.x << "," << point.y << "\n";
    }
    return 0;
}