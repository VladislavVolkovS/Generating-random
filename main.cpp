#include "halton.h"
#include <iostream>
#include <fstream>
#include "sobol.h"

const int SAMPLE_INDEXES = 8;

int main() {
    const uint32_t dimension = 10;
    for (uint32_t dim = 0; dim <= dimension; ++dim) {
        const uint32_t base = Primes[dim & 31u];
        std::ofstream csv;
        std::string name = "halton_" + std::to_string(SAMPLE_INDEXES) + "_" + std::to_string(dim)
                        + "dim.csv";
        csv.open(name);
        csv.clear();
        csv << "Dimension,Value,\n";
        for (int sampleIdx = 0; sampleIdx < SAMPLE_INDEXES; ++sampleIdx) {
            csv << dim << "," << halton_scramble(sampleIdx, base) << ",\n";
            // std::cout << dim << "," << halton_scramble(sampleIdx, base) << ",\n";
        }

    }

    // for (uint32_t dim = 0; dim <= dimension; ++dim) {
    //     const uint32_t base = Primes[dim & 31u];
    //     std::ofstream csv;
    //     std::string name = "sobol_" + std::to_string(SAMPLE_INDEXES) + "_" + std::to_string(dim)
    //                     + "dim.csv";
    //     csv.open(name);
    //     csv.clear();
    //     csv << "Dimension,Value,\n";
    //     for (int sampleIdx = 0; sampleIdx < SAMPLE_INDEXES; ++sampleIdx) {
    //         csv << dim << "," << sobol_scramble(sampleIdx, base) << ",\n";
    //         // std::cout << dim << "," << sobol(sampleIdx, base) << ",\n";
    //     }

    // }
    return 0;
}