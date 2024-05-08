#pragma once
#include <iostream>

enum struct SampleDimension : uint32_t {
    ePixelX,
    ePixelY,
    eLightId,
    eLightPointX,
    eLightPointY,
    eBSDF0,
    eBSDF1,
    eBSDF2,
    eBSDF3,
    eRussianRoulette,
    eNUM_DIMENSIONS
};

struct SamplerState {
    uint32_t seed;
    uint32_t sampleIdx;
    uint32_t pixelX, pixelY;
    uint32_t bn_offset;
};

uint32_t jenkins_hash(unsigned int a);

SamplerState initSampler(uint32_t pixelX, uint32_t pixelY, uint32_t linearPixelIndex, uint32_t pixelSampleIndex, uint32_t seed = 0,
                         uint32_t samplesPerPixel = 1, uint8_t gen_type = 0, uint32_t bn_offset = 0);