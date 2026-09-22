#include <cstdint>
#include <iostream>
#include <random>
#include <vector>

#include "timer.h"

constexpr size_t SIZE = 16000000;
constexpr size_t COLUMNS = 4000;
constexpr size_t ROWS = 4000;
int main() {
    Timer timer;
    std::vector<uint64_t> vector_one(SIZE);
    std::vector<uint64_t> vector_two(SIZE);
    std::uint64_t sum = 0;
    std::mt19937_64 rng(0);

    //Row Major Fill
    rng.seed(0);
    for (uint64_t r = 0; r < ROWS; r++) {
        for (uint64_t c = 0; c < COLUMNS; c++) {
            vector_one[r * COLUMNS + c] = rng();
        }
    }

    //Row Major Sum
    timer.restart();
    for (uint64_t r = 0; r < ROWS; r++) {
        for (uint64_t c = 0; c < COLUMNS; c++) {
            sum += vector_one[r * COLUMNS + c];
        }
    }
    std::cout << timer.glance<Timer::microseconds>() << " " << sum << std::endl;

    //Column Major Fill
    rng.seed(0);
    for (uint64_t c = 0; c < COLUMNS; c++) {
        for (uint64_t r = 0; r < ROWS; r++) {
            vector_two[c * ROWS + r] = rng();
        }
    }

    //Column Major Sum
    sum = 0;
    timer.restart();
    for (uint64_t c = 0; c < COLUMNS; c++) {
        for (uint64_t r = 0; r < ROWS; r++) {
            sum += vector_two[c * ROWS + r];
        }
    }
    std::cout << timer.glance<Timer::microseconds>() << " " << sum << std::endl;

    return 0;
}
