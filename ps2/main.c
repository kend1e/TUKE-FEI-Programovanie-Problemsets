#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "k.h"
#include "hof.h"
#include "ui.h"

int main()
{
    struct player list[10];
    struct player player = {
        .name = "manager",
        .score = 1500
    };
    int size = load(list);
    add_player(list, &size, player);
    save(list, size);

    struct game game = {
        .board = {
            {'A', ' ', ' ', ' '},
            {'B', ' ', ' ', 'B'},
            {'C', 'C', 'C', ' '},
            {'D', 'D', 'D', 'D'}
        },
        .score = 0
    };

    add_random_tile(&game);
    update(&game, 0, 1);
    
    is_game_won(game);
    is_move_possible(game);

    render(game);
}