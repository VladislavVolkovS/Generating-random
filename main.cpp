#include <iostream>
#include <fstream>
#include "random.h"
#include "consol_reader.h"

int main(int argc, const char* argv[]) {
    auto params = ReadParams(argc, argv);

    std::ofstream pixel;
    std::string params_txt = "params.txt";
    std::string name_gen;
    // params.gen_type = UNIFORM;
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
        case 4:
            name_gen = "UNIFORM";
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

    std::vector<float> blueNoiseData;
    createBlueNoiseBuffer(blueNoiseData);
    for (int i = 1; i <= params.samples_per_pixel; ++i) {
        uint32_t seed = 42;
        switch (params.gen_type)
        {
        case UNIFORM /* Uniform*/:
            // seed = prd.sampleIndex + prd.linearPixelIndex * params.maxSampleCount;
            seed = initRNG(params.pixelX, params.pixelY, params.width, i);
            break;
        case HALTON /* Halton */:
            /* seed depends on pixel*/
            seed = jenkins_hash(params.linearPixelIndex) + i;
            break;
        case SOBOL /* Sobol */:
            /* seed depends on pixel */
            seed = params.linearPixelIndex;
            break;
        case BLUE_NOISE /* Blue noise*/:
            seed = params.linearPixelIndex;
            break;
        default:
            break;
        }
        auto state = initSampler(params.pixelX, params.pixelY, params.linearPixelIndex, i, seed, params.samples_per_pixel,
                                 (uint8_t)params.gen_type, i);

        float x = random(state, params.dim[0], params.gen_type, params.scrambling, blueNoiseData.data(), 256);
        float y = random(state, params.dim[1], params.gen_type, params.scrambling, blueNoiseData.data(), 256);

        csv << x << "," << y << ",\n";
    }

    csv.close();

    return 0;
}