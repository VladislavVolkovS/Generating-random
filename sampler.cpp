#include "sampler.h"

uint32_t jenkins_hash(unsigned int x) {
      x += x << 10;
      x ^= x >> 6;
      x += x << 3;
      x ^= x >> 11;
      x += x << 15;
      return x;
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

SamplerState initSampler(uint32_t pixelX, uint32_t pixelY, uint32_t linearPixelIndex, uint32_t pixelSampleIndex, uint32_t seed,
                         uint32_t samplesPerPixel, uint8_t gen_type, uint32_t bn_offset) {
    SamplerState sampler {};
    sampler.pixelX = pixelX;
    sampler.pixelY = pixelY;
    sampler.seed = seed;
    sampler.sampleIdx = pixelSampleIndex + linearPixelIndex * samplesPerPixel;
    sampler.bn_offset = bn_offset;
    
  return sampler;
}