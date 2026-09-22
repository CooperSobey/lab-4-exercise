#pragma once
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

/*
 *Idea:
 *Say we had 0b1111, 0b2222, 0b3333 (i know thats not real but for clarity)
 *If we expand them all by 3, we'd get ex: 001001001001
 *for 0b2222 we'd have to shift it by 1 after so we'd get 0020020020020
 *same for 0b3333. If we then add them we got our morton3d. We then chop off the front 2 0's and were good.
 *But they don't matter anyways and will automatically get cut off if we hit 64 bits
 */
inline uint64_t morton3d(uint64_t x, uint64_t y, uint64_t z) {
    uint64_t expanded_x = expand(x, 3);
    uint64_t expanded_y = expand(y, 3);
    uint64_t expanded_z = expand(z, 3);

    expanded_y = expanded_y << 1;
    expanded_z = expanded_z << 2;
    uint64_t morton_sum = expanded_x + expanded_y + expanded_z;
    
    return morton_sum;
}