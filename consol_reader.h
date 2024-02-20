#pragma once

#include "cxxopts.hpp"
#include "sampler.h"
#include "random.h"
#include <array>

struct Parameters {
    std::array<SampleDimension, 2> dim;
    uint32_t linearPixelIndex;
    uint32_t samples_per_pixel;
    Generator gen_type;
    bool scrambling;
};

Parameters ReadParams(int argc, const char* argv[]) {
    cxxopts::Options options("sampler <params>", "commands");
    options.add_options()

        ("w, width", "screen width", cxxopts::value<uint32_t>()->default_value("800"))
        ("h, height", "screen height", cxxopts::value<uint32_t>()->default_value("600"))

        ("spp", "samples per pixel", cxxopts::value<uint32_t>()->default_value("256"))

        ("pixelX", "pixel horizontal position", cxxopts::value<uint32_t>()->default_value("0"))
        ("pixelY", "pixel vertical position", cxxopts::value<uint32_t>()->default_value("0"))

        ("dimX", "dimension to output as x", cxxopts::value<uint32_t>()->default_value("0"))
        ("dimY", "dimension to output as y", cxxopts::value<uint32_t>()->default_value("1"))

        ("gen_type", "type of random generator", cxxopts::value<uint32_t>()->default_value("0"))

        ("scramble", "scrambling", cxxopts::value<bool>()->default_value("0"))
    ;

    auto result = options.parse(argc, argv);

    auto screenWidth = result["width"].as<uint32_t>();
    auto screenHeight = result["height"].as<uint32_t>();

    auto spp = result["spp"].as<uint32_t>();

    auto dimX = static_cast<SampleDimension>(result["dimX"].as<uint32_t>());
    auto dimY = static_cast<SampleDimension>(result["dimY"].as<uint32_t>());

    auto pixelX = result["pixelX"].as<uint32_t>();
    auto pixelY = result["pixelY"].as<uint32_t>();

    auto gen_type = static_cast<Generator>(result["gen_type"].as<uint32_t>());

    auto scramble = result["scramble"].as<bool>();

    return Parameters{
        {dimX, dimY},
        pixelY * screenWidth + pixelX,
        spp,
        gen_type,
        scramble
    };
}