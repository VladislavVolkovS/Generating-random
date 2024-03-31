#include "blue_noise.h"
#include "fstream"

int main() {
    BlueNoiseData data{};
    data.radius = 0.05f;
    data.n_looked_points = 100;
    BlueNoise(&data);

    std::ofstream file;
    file.open("blue_noise_res.csv");
    for (const auto& point : data.points) {
        file << point[0] << "," << point[1] << "\n";
    }
    return 0;
}