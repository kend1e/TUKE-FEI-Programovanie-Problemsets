#include <stdio.h>
#include <curses.h>
#include <string.h>

#include "k.h"

//void render(const struct game game){
//    printf("score: %d\n", game.score);
//
//    for(int row = 0; row < SIZE; row++){
//        printf("+---+---+---+---+\n|");
//        for(int col = 0; col < SIZE; col++){
//            printf(" %c |", game.board[row][col]);
//        }
//        printf("\n");
//    }
//    printf("+---+---+---+---+\n");
//}

void render(const struct game game){
    clear();
    char text[20];
    sprintf(text, "Score: %d", game.score);
    attrset(COLOR_PAIR(0));
    mvprintw(1, (COLS - (int)strlen(text)) / 2, text);
    int x_start = (COLS - 25) / 2;
    int y_start = 3;
    attrset(COLOR_PAIR(6));

    for (int y = y_start; y < y_start + 17; y++){
        for (int x = x_start; x < x_start + 25; x++){
            mvprintw(y, x, " ");
        }
    }

    for (int y = 0; y < SIZE; y++){
        for (int x = 0; x < SIZE; x++) {
            if (game.board[y][x] == ' ')
                attrset(COLOR_PAIR(0));
            else if (game.board[y][x] < 'C')
                attrset(COLOR_PAIR(1));
            else if (game.board[y][x] < 'E')
                attrset(COLOR_PAIR(2));
            else if (game.board[y][x] < 'G')
                attrset(COLOR_PAIR(3));
            else if (game.board[y][x] < 'J')
                attrset(COLOR_PAIR(4));
            else
                attrset(COLOR_PAIR(5));

            mvprintw(y_start + (y * SIZE) + 1, x_start + (x * 6) + 1, "     ");
            mvprintw(y_start + (y * SIZE) + 2, x_start + (x * 6) + 1, "  %c  ", game.board[y][x]);
            mvprintw(y_start + (y * SIZE) + 3, x_start + (x * 6) + 1, "     ");
        }
    }

    refresh();
}
