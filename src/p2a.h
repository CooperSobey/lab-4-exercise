
#include <cstdint>
inline uint64_t expand(uint64_t input, uint32_t scale) {
    uint64_t expanded = 0;

    for (uint64_t i = 0; i < 64; i++) {
        const uint64_t long_num = 1;
        uint64_t bit = long_num & (input >> i);

        uint64_t shift = i * scale;
        if (shift >= 64) {
            continue;
        }
        expanded |= (bit << shift);

    }

    return expanded;  // replace this with your impl!
}