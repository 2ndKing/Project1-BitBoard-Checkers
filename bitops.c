// bitops.c
#include "bitops.h"

uint64_t SetBit(uint64_t value, int position) {
    if (position < 0 || position > 63) return value;
    return value | (1ULL << position);
}

uint64_t ClearBit(uint64_t value, int position) {
    if (position < 0 || position > 63) return value;
    return value & ~(1ULL << position);
}

uint64_t ToggleBit(uint64_t value, int position) {
    if (position < 0 || position > 63) return value;
    return value ^ (1ULL << position);
}

int GetBit(uint64_t value, int position) {
    if (position < 0 || position > 63) return 0;
    return (value >> position) & 1ULL;
}

int CountBits(uint64_t value) {
    int count = 0;
    while (value) {
        count += value & 1ULL;
        value >>= 1;
    }
    return count;
}

uint64_t ShiftLeft(uint64_t value, int positions) {
    if (positions <= 0) return value;
    return value << positions;
}

uint64_t ShiftRight(uint64_t value, int positions) {
    if (positions <= 0) return value;
    return value >> positions;
}

void PrintBinary64(uint64_t value) {
    for (int i = 63; i >= 0; i--) {
        printf("%d", (int)((value >> i) & 1ULL));
        if (i % 8 == 0) printf(" ");
    }
    printf("\n");
}
