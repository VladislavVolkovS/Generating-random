#include "halton.h"
#include <iostream>
#include <fstream>
#include "random.h"
#include "consol_reader.h"
#include "blue_noise.h"

int main(int argc, const char* argv[]) {
    auto params = ReadParams(argc, argv);

    std::ofstream pixel;
    std::string params_txt = "params.txt";
    std::string name_gen;
    switch (params.gen_type) {
        case 0:
            name_gen = "STL";
            break;
        case 1:
            name_gen = "HALTON";
            break;
        case 2:
            name_gen = "SOBOL";
            break;
        case 3:
            name_gen = "BLUE_NOISE";
        default:
            break;
    }
    pixel.open(params_txt);
    pixel.clear();
    pixel << name_gen + " " << params.linearPixelIndex << " " << params.samples_per_pixel << " " <<
             static_cast<uint32_t>(params.dim[0]) << " " << static_cast<uint32_t>(params.dim[1]);
    pixel.close();

    std::ofstream csv;
    std::string csv_name = "sample_result.csv";
    csv.open(csv_name);
    csv.clear();
    csv << "x,y,\n";

    BlueNoiseData data{};

    // values for 256 points but distributions are equal
    data.radius = 0.05005f;

    if (name_gen == "BLUE_NOISE") {
        BlueNoise(&data);
        for (int i = 0; i < params.samples_per_pixel; ++i) {

            float x = data.points[i % params.samples_per_pixel][0];
            float y = data.points[i % params.samples_per_pixel][1];

            csv << x << "," << y << ",\n";
        }
        csv.close();
        return 0;
    }

    for (int i = 0; i < params.samples_per_pixel; ++i) {
        auto state = initSampler(params.linearPixelIndex, i, 1, params.samples_per_pixel,
                                 (uint8_t)params.gen_type);

        float x = random(state, params.dim[0], params.gen_type, params.scrambling);
        float y = random(state, params.dim[1], params.gen_type, params.scrambling);

        csv << x << "," << y << ",\n";
    }

    csv.close();

    return 0;
}