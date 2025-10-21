#include "game.h"
#include <stdio.h>

int main(void) {
    GameState g;
    InitBoard(&g);

    printf("BitBoard Checkers - OwlTech Edition\n");
    PrintBoard(&g);
    printf("To move, enter current position and next position (from 0-63). Ex: 8 17"
           "\nRed goes up, black goes down\n\n");

    while (1) {
        int from, to;
        printf("%s’s move: ",
               g.turn == RED ? "RED" : "BLACK");

        if (scanf("%d %d", &from, &to) != 2) {
            printf("Invalid input. Please enter two integers (Ex: 12 16).\n");
            while (getchar() != '\n'); // clear bad input
            continue;
        }

        if (!MovePiece(&g, from, to)) {
            printf("❌ Invalid move. Try again.\n");
            continue;
        }

        PrintBoard(&g);

        int win = CheckWin(&g);
        if (win != -1) {
            printf("🏁 %s wins!\n", win == RED ? "RED" : "BLACK");
            break;
        }
    }

    return 0;
}
