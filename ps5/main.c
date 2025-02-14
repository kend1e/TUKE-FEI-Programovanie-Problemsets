#include"game.h"

int main()
{
    struct game *game = create_game();

    play_game(game);

    destroy_game(game);

    return 0;
}