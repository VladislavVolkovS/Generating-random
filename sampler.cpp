#include "sampler.h"

uint32_t jenkins_hash(unsigned int a) {
      a = (a + 0x7ED55D16) + (a << 12);
      a = (a ^ 0xC761C23C) ^ (a >> 19);
      a = (a + 0x165667B1) + (a << 5);
      a = (a + 0xD3A2646C) ^ (a << 9);
      a = (a + 0xFD7046C5) + (a << 3);
      a = (a ^ 0xB55A4F09) ^ (a >> 16);
      return a;
}

uint32_t MortonHash(uint32_t x) {
    x &= 0x0000ffff;                  // x = ---- ---- ---- ---- fedc ba98 7654 3210
    x = (x ^ (x <<  8)) & 0x00ff00ff; // x = ---- ---- fedc ba98 ---- ---- 7654 3210
    x = (x ^ (x <<  4)) & 0x0f0f0f0f; // x = ---- fedc ---- ba98 ---- 7654 ---- 3210
    x = (x ^ (x <<  2)) & 0x33333333; // x = --fe --dc --ba --98 --76 --54 --32 --10
    x = (x ^ (x <<  1)) & 0x55555555; // x = -f-e -d-c -b-a -9-8 -7-6 -5-4 -3-2 -1-0
    return x;
}

uint32_t EncodeMorton(uint32_t x, uint32_t y) {
  return (MortonHash(y) << 1) + MortonHash(x);
}

SamplerState initSampler(uint32_t linearPixelIndex, uint32_t pixelSampleIndex, uint32_t seed,
                         uint32_t samplesPerPixel, uint8_t gen_type) {
    SamplerState sampler {};

    switch (gen_type)
    {
    case 1:
        sampler.seed = jenkins_hash(linearPixelIndex) + pixelSampleIndex; // better for halton
        break;
    case 2:
        sampler.seed = pixelSampleIndex + linearPixelIndex * samplesPerPixel; // better for sobol
        break;
    default:
        sampler.seed = seed + pixelSampleIndex; // default
        break;
    }
    
    sampler.sampleIdx = pixelSampleIndex;
    // sampler.sampleIdx =
    //     EncodeMorton(linearPixelIndex / 1024, linearPixelIndex % 1024) * samplesPerPixel +
    //     pixelSampleIndex; // Morton Hash
    
  return sampler;
}