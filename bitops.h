// bitops.h
#ifndef BITOPS_H
#define BITOPS_H

#include <stdio.h>
#include <stdint.h>

uint64_t SetBit(uint64_t value, int position);
uint64_t ClearBit(uint64_t value, int position);
uint64_t ToggleBit(uint64_t value, int position);
int GetBit(uint64_t value, int position);
int CountBits(uint64_t value);
uint64_t ShiftLeft(uint64_t value, int positions);
uint64_t ShiftRight(uint64_t value, int positions);
void PrintBinary64(uint64_t value);

#endif
