#include "halton.h"
#include <iostream>
#include <fstream>
#include "random.h"
#include "consol_reader.h"

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