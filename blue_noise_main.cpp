#include "blue_noise.h"
#include "fstream"

int main() {
    BlueNoiseData data{};
    BlueNoise(&data);

    std::ofstream file;
    file.open("blue_noise_res.csv");
    for (const auto& point : data.points) {
        file << point[0] << "," << point[1] << "\n";
    }
    return 0;
}