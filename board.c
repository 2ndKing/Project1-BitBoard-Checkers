#include "board.h"
#include "game.h"
#include <stdio.h>

void InitBoard(GameState *g) {
    // Black occupies the top 3 rows (rows 6–8) on dark squares
    g->black = 0xAA55AA0000000000ULL;  // rows 5–7 in bit order

    // Red occupies the bottom 3 rows (rows 1–3) on dark squares
    g->red   = 0x000000000055AA55ULL;  // rows 0–2 in bit order

    g->red_kings = 0;
    g->black_kings = 0;
    g->turn = RED; // red starts
}

uint64_t GetAllPieces(const GameState *g) {
    return g->red | g->black | g->red_kings | g->black_kings;
}

int IsOccupied(const GameState *g, int pos) {
    return GetBit(GetAllPieces(g), pos);
}

void PrintBoard(const GameState *g) {
    printf("\n    A B C D E F G H\n");

    for (int row = 7; row >= 0; row--) {
        printf("%d | ", row + 1);

        for (int col = 0; col < 8; col++) {
            int pos = row * 8 + col;
            uint64_t mask = 1ULL << pos;
            char c = '.';

            if (g->red & mask) c = 'r';
            if (g->black & mask) c = 'b';
            if (g->red_kings & mask) c = 'R';
            if (g->black_kings & mask) c = 'B';

            printf("%c ", c);
        }
        printf("|\n");
    }
    printf("    ----------------\n");
    printf("Score  |  RED: %2d   BLACK: %2d\n",
           GetRedScore(g), GetBlackScore(g));
    printf("\n");

}


