#ifndef GAME_H
#define GAME_H

#include "board.h"

int MovePiece(GameState *g, int from, int to);
int CapturePiece(GameState *g, int from, int over, int to);
void PromoteKings(GameState *g);
int CheckWin(const GameState *g);

#endif
