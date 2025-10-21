#ifndef BOARD_H
#define BOARD_H

#include <stdint.h>
#include "bitops.h"

#define RED 0
#define BLACK 1

typedef struct {
    uint64_t red;
    uint64_t black;
    uint64_t red_kings;
    uint64_t black_kings;
    int turn; // 0 = red, 1 = black
} GameState;

void InitBoard(GameState *g);
void PrintBoard(const GameState *g);
uint64_t GetAllPieces(const GameState *g);
int IsOccupied(const GameState *g, int position);

#endif
