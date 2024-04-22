#include <iostream>
#include <vector>
#include <array>
#include <cmath>
#include <string>
#include <fstream>

using Color = std::array<float, 3>;

const int size = 64;

void SaveCSV(std::vector<std::vector<Color>>& mask, const std::string file_name) {
    std::ofstream file;
    file.open(file_name);
    for (const auto& vec : mask) {
        for (const auto& col : vec) {
            file << col[0] << ", ";
        }
        file << "\n";
    }
    file.close();
}

void Swap(std::vector<std::vector<Color>>& mask, int px, int py, int qx, int qy) {
    Color tmp = mask[px][py];
    mask[px][py] = mask[qx][qy];
    mask[qx][qy] = tmp;
}

const float sigma_i = 2.1f;
const float sigma_s = 1.0f;

float GetEnergy(std::vector<std::vector<Color>>& mask, int ix, int iy) {
    float sum[size] = {};

#pragma omp parallel for schedule(dynamic, 1) num_threads(7)
    for (int oy = -7; oy <= 7; ++oy) {
        for (int ox = -7; ox <= 7; ++ox) {
            int sx = ix + ox;
            if (sx < 0)
                sx += size;
            if (sx >= size)
                sx -= size;

            int sy = iy + oy;
            if (sy < 0)
                sy += size;
            if (sy >= size)
                sy -= size;

            float dx = std::abs(ix - sx);
            if (dx > size / 2)
                dx = size - dx;

            float dy = std::abs(iy - sy);
            if (dy > size / 2)
                dy = size - dy;
            const float a =
                (dx * dx + dy * dy) / (sigma_i * sigma_i);

            const float b = std::sqrt(std::abs(mask[ix][iy][0] - mask[sx][sy][0])) / (sigma_s * sigma_s);

            sum[sy] += std::exp(-a - b);
        }
    }

    float total = 0;
    for (int sy = 0; sy < size; ++sy)
        total += sum[sy];
    return total;
}

class Random {
private:
    uint64_t x;
public:
    uint64_t next(void) { 
        x ^= x >> 12; // a
        x ^= x << 25; // b
        x ^= x >> 27; // c
        return x * 2685821657736338717LL;
    }

    float next01(void) {
        return (float)((double)next() / std::numeric_limits<uint64_t>::max());
    }

    // [0, 1)
    float nextc01o(void) {
        return (float)((uint32_t)(next() >> 1) / 4294967296.0);
    }

    // [min_value, max_value]
    float next(float min_value, float max_value) {
        const double inv = (max_value - min_value);
        return (float)(((double)next() * (inv / std::numeric_limits<uint64_t>::max())) + min_value);
    }

    Random(uint64_t initial_seed) {
        if (initial_seed == 0)
            x = 0xDEADBEEFDEADBEEF;
        else
            x = initial_seed;
    }
};

int main()
{
    std::vector<std::vector<Color>> mask(size, std::vector<Color>(size));

    Random random{0};

    // init random mask
    for (int iy = 0; iy < size; ++iy) {
        for (int ix = 0; ix < size; ++ix) {
            const float r = random.next01();
            mask[ix][iy] = Color{r, r, r};
        }
    }

    SaveCSV(mask, "visual/start_noise.csv");

    // initial energy
    float energy[size][size] = {};

    for (int iy = 0; iy < size; ++iy) {
        for (int ix = 0; ix < size; ++ix) {
            energy[iy][ix] = GetEnergy(mask, ix, iy);
        }
    }

    const int kMaxIteration = 1'000'000;

    for (int ite = 0; ite < kMaxIteration; ++ite) {
        float current_energy = 0;

        for (int iy = 0; iy < size; ++iy) {
            for (int ix = 0; ix < size; ++ix) {
                current_energy += energy[iy][ix];
            }
        }

        if (ite % 10'000 == 0) {
            std::cout << "Iteration: " << ite << ", " << "Energy: " << current_energy << '\r' << std::flush;
        }


        const int px = random.next() % size;
        const int py = random.next() % size;
        const int qx = random.next() % size;
        const int qy = random.next() % size;

        float next_energy = current_energy;
        next_energy -= energy[py][px];
        next_energy -= energy[qy][qx];

        Swap(mask, px, py, qx, qy);

        const float e0 = GetEnergy(mask, px, py);
        const float e1 = GetEnergy(mask, qx, qy);

        next_energy += (e0 + e1);

        if (next_energy < current_energy) {
            energy[py][px] = e0;
            energy[qy][qx] = e1;
            continue;
        }
        Swap(mask, px, py, qx, qy);
    }

    SaveCSV(mask, "visual/blue_noise_1D.csv");

    return 0;
}