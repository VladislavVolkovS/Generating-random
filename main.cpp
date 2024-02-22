#include "halton.h"
#include <iostream>
#include <fstream>
#include "random.h"
#include "consol_reader.h"

// const int SAMPLE_INDEXES = 8;

// int main() {
//     const uint32_t dimension = 10;
//     for (uint32_t dim = 0; dim <= dimension; ++dim) {
//         const uint32_t base = Primes[dim & 31u];
//         std::ofstream csv;
//         std::string name = "halton_" + std::to_string(SAMPLE_INDEXES) + "_" + std::to_string(dim)
//                         + "dim.csv";
//         csv.open(name);
//         csv.clear();
//         csv << "Dimension,Value,\n";
//         for (int sampleIdx = 0; sampleIdx < SAMPLE_INDEXES; ++sampleIdx) {
//             csv << dim << "," << halton_scramble(sampleIdx, base) << ",\n";
//             // std::cout << dim << "," << halton_scramble(sampleIdx, base) << ",\n";
//         }

//     }

//     // for (uint32_t dim = 0; dim <= dimension; ++dim) {
//     //     const uint32_t base = Primes[dim & 31u];
//     //     std::ofstream csv;
//     //     std::string name = "sobol_" + std::to_string(SAMPLE_INDEXES) + "_" + std::to_string(dim)
//     //                     + "dim.csv";
//     //     csv.open(name);
//     //     csv.clear();
//     //     csv << "Dimension,Value,\n";
//     //     for (int sampleIdx = 0; sampleIdx < SAMPLE_INDEXES; ++sampleIdx) {
//     //         csv << dim << "," << sobol_scramble(sampleIdx, base) << ",\n";
//     //         // std::cout << dim << "," << sobol(sampleIdx, base) << ",\n";
//     //     }

//     // }
//     return 0;
// } 0-1 3-4

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
        auto state = initSampler(params.linearPixelIndex, i, 0);

        float x = random(state, params.dim[0], params.gen_type, params.scrambling);
        float y = random(state, params.dim[1], params.gen_type, params.scrambling);

        csv << x << "," << y << ",\n";
    }

    csv.close();

    return 0;
}