#include <cstdint>
#include <format>
#include <iostream>
#include <random>
#include <vector>

#include "p2a.h"
#include "timer.h"
constexpr size_t PLANES = 256;
constexpr size_t COLUMNS = 256;
constexpr size_t ROWS = 256;
constexpr size_t KX = 4, KY = 4, KZ = 4, STRIDE = 4;

int main() {
    Timer timer;
    std::vector<uint64_t> vector_one(PLANES * ROWS * COLUMNS);
    std::vector<uint64_t> vector_two(PLANES * ROWS * COLUMNS);

    std::mt19937_64 rng(0);

    //Make our 3D arrays
    rng.seed(0);
    for (uint64_t p = 0; p < PLANES; p++) {
        for (uint64_t r = 0; r < ROWS; r++) {
            for (uint64_t c = 0; c < COLUMNS; c++) {
                uint64_t index = (p * ROWS + r) * COLUMNS + c;
                vector_one[index] = rng();
                vector_two[morton3d(c, r, p)] = vector_one[index];
            }
        }
    }

    std::vector<uint64_t> kernal_one(KZ * KY * KX);
    std::vector<uint64_t> kernal_two(KZ * KY * KX);

    //Make our two kernals
    for (uint64_t z = 0; z < KZ; z++) {
        for (uint64_t y = 0; y < KY; y++) {
            for (uint64_t x = 0; x < KX; x++) {
                uint64_t value = x + y + z;
                kernal_one[(z * KY + y) * KX + x] = value;
                kernal_two[morton3d(x, y, z)] = value;
            }
        }
    }

    const uint64_t convolve_plane = ((PLANES - KZ) / STRIDE) + 1;
    const uint64_t convolve_row = ((ROWS - KY) / STRIDE) + 1;
    const uint64_t convolve_column = ((COLUMNS - KX) / STRIDE) + 1;

    std::vector<uint64_t> row_convolve(convolve_plane * convolve_row * convolve_column);
    std::vector<uint64_t> morton_convolve(convolve_plane * convolve_row * convolve_column);
    uint64_t dot_sum;

    timer.restart();
    for (uint64_t i = 0; i < convolve_plane; i++) {
        for (uint64_t j = 0; j < convolve_row; j++) {
            for (uint64_t k = 0; k < convolve_column; k++) {
                dot_sum = 0;
                
                for (uint64_t z = 0; z < KZ; z++) {
                    for (uint64_t y = 0; y < KY; y++) {
                        for (uint64_t x = 0; x < KX; x++) {

                        }
                    }
                }
            }
        }
    }

    std::cout << timer.glance<Timer::microseconds>() << std::endl;



    return 0;
}
