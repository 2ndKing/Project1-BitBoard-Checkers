#include "game.h"
#include <stdio.h>
#include <stdlib.h>

static inline int col(int idx) { return idx & 7; }          // 0..7
static inline int row(int idx) { return idx >> 3; }          // 0..7

static int square_empty(const GameState *g, int pos) {
    uint64_t m = 1ULL << pos;
    return !((g->red | g->black | g->red_kings | g->black_kings) & m);
}

static int has_my_piece(const GameState *g, int pos) {
    uint64_t m = 1ULL << pos;

    if (g->turn == RED) return !!((g->red | g->red_kings) & m);
    else                return !!((g->black | g->black_kings) & m);
}

static int is_king(const GameState *g, int pos) {
    uint64_t m = 1ULL << pos;

    if (g->turn == RED) return !!(g->red_kings & m);
    else                return !!(g->black_kings & m);
}

static int is_enemy_at(const GameState *g, int pos) {
    uint64_t m = 1ULL << pos;

    if (g->turn == RED) return !!((g->black | g->black_kings) & m);
    else                return !!((g->red  | g->red_kings)   & m);
}

static void remove_enemy_at(GameState *g, int pos) {
    uint64_t m = 1ULL << pos;

    if (g->turn == RED) { g->black &= ~m; g->black_kings &= ~m; }
    else                { g->red   &= ~m; g->red_kings   &= ~m; }
}

void PromoteKings(GameState *g) {
    uint64_t topRow    = 0xFF00000000000000ULL; // indices 56..63
    uint64_t bottomRow = 0x00000000000000FFULL; // indices 0..7

    g->red_kings   |= (g->red   & topRow);
    g->black_kings |= (g->black & bottomRow);
}

int GetRedScore(const GameState *g) {
    int redMen   = CountBits(g->red);
    int redKings = CountBits(g->red_kings);
    return redMen + 2 * redKings; // kings worth double
}

int GetBlackScore(const GameState *g) {
    int blackMen   = CountBits(g->black);
    int blackKings = CountBits(g->black_kings);
    return blackMen + 2 * blackKings;
}


// returns 1 on success, 0 invalid
int MovePiece(GameState *g, int from, int to) {
    // Basic bounds and ownership
    if (from < 0 || from > 63 || to < 0 || to > 63) return 0;
    if (!has_my_piece(g, from)) return 0;
    if (!square_empty(g, to))   return 0;

    int dcol = col(to) - col(from);
    int drow = row(to) - row(from);
    int adcol = dcol < 0 ? -dcol : dcol;
    int adrow = drow < 0 ? -drow : drow;

    int king = is_king(g, from);

    // SIMPLE MOVE: exactly one diagonal step
    // men must move forward: RED rows increase (+1), BLACK rows decrease (-1)
    int forward_ok = king || (g->turn == RED ? (drow == 1) : (drow == -1));
    int simple_ok  = (adcol == 1 && adrow == 1 && forward_ok);

    // CAPTURE MOVE: exactly two diagonal steps with enemy in middle
    int is_capture = 0;
    if (adcol == 2 && adrow == 2) {
        int mid = (from + to) / 2;

        // For men, direction must still be forward unless king
        int cap_forward_ok = king || (g->turn == RED ? (drow == 2) : (drow == -2));
        if (cap_forward_ok && is_enemy_at(g, mid) && square_empty(g, to)) {
            is_capture = 1;
        } else {
            is_capture = 0;
        }
    }

    if (!simple_ok && !is_capture) return 0; // no long slides, only 1 step or capture

    // --- Apply the move ---
    uint64_t fromM = 1ULL << from;
    uint64_t toM   = 1ULL << to;

    if (g->turn == RED) {

        // Move from regular or king bitboard appropriately
        if (g->red_kings & fromM) { g->red_kings &= ~fromM; g->red_kings |= toM; }
        else                      { g->red       &= ~fromM; g->red       |= toM; }
    } else {
        if (g->black_kings & fromM) { g->black_kings &= ~fromM; g->black_kings |= toM; }
        else                        { g->black       &= ~fromM; g->black       |= toM; }
    }

    // If captured, remove enemy at midpoint
    if (is_capture) {
        int mid = (from + to) / 2;
        remove_enemy_at(g, mid);
    }

    // Promotion after landing
    PromoteKings(g);

    // End turn (no multi-jump chaining for now)
    g->turn = 1 - g->turn;
    return 1;
}

int CapturePiece(GameState *g, int from, int over, int to) {
    // You can route to MovePiece and validate that 'to' is 2 steps and 'over' matches.
    (void)over;
    return MovePiece(g, from, to);
}

int CheckWin(const GameState *g) {
    if ((g->red | g->red_kings) == 0)   return BLACK;
    if ((g->black | g->black_kings) == 0) return RED;
    return -1;
}
