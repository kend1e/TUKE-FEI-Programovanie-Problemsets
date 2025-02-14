#include <stdlib.h>

#include "k.h"

#define tile_at(game, params) game->board[params.row][params.col]
#define tile_at_index(game, params, index) *_tile_at_index(game, params, index)

#define handle_last_empty_cell(params, last_empty_cell) (params.is_positive ? (*last_empty_cell)-- : (*last_empty_cell)++)
#define get_dim_coord(params) (params.is_horizontal ? params.col : params.row)

struct line_handle_params
{
    int row, col;
    bool is_horizontal;
    bool is_positive;
};

struct prev_tile_info
{
    char tile;
    int index;
};

bool handle_update(struct game *game, struct line_handle_params params);
bool handle_line_increment(struct game *game, struct line_handle_params params, struct prev_tile_info *prev_tile);
bool handle_line_order(struct game *game, struct line_handle_params params, int *last_empty_cell);

char* _tile_at_index(struct game *game, struct line_handle_params params, int index);
char incrementTile(char tile, int *score);

void add_random_tile(struct game *game)
{
    int row, col;

    do {
        row = rand() % SIZE;
        col = rand() % SIZE;
    } while(game->board[row][col] != ' ');

    game->board[row][col] = (rand() % 2) ? 'B' : 'A';
}

bool update(struct game *game, int dy, int dx)
{
    if(dx != 0 && dy != 0)
        return false;

    if(dx == 0 && dy == 0)
        return false;

    if(dx > 1 || dx < -1 || dy > 1 || dy < -1)
        return false;

    struct line_handle_params params = {0};

    params.is_horizontal = dx != 0;
    params.is_positive = (params.is_horizontal && dx == 1) || (!params.is_horizontal && dy == 1);

    return handle_update(game, params);
}

bool is_move_possible(const struct game game)
{
    for(int row = 0; row < SIZE; ++row)
        for(int col = 0; col < SIZE; ++col)
        {
            if(game.board[row][col] == ' ')
                return true;
            
            if(row % 2 != col % 2)
                continue;
            
            char c = game.board[row][col];

            if(row >= 1 && game.board[row - 1][col] == c)
                return true;
            if(row < SIZE - 1 && game.board[row + 1][col] == c)
                return true;

            if(col >= 1 && game.board[row][col - 1] == c)
                return true;
            if(col < SIZE - 1 && game.board[row][col + 1] == c)
                return true;
        }
    return false;
}

bool is_game_won(const struct game game)
{
    for(int row = 0; row < SIZE; ++row)
        for(int col = 0; col < SIZE; ++col)
        {
            if(game.board[row][col] != 'K')
                continue;
            return true;
        }
    return false;
}

bool handle_update(struct game *game, struct line_handle_params params)
{
    bool update_flag = false;

    struct prev_tile_info prev_tile;
    int last_empty_cell;

    int *iter_i, *iter_j;
    if(params.is_horizontal)
    {
        iter_i = &params.row;
        iter_j = &params.col;
    }
    else
    {
        iter_i = &params.col;
        iter_j = &params.row;
    }

    for(*iter_i = 0; *iter_i < SIZE; ++*iter_i)
    {
        prev_tile.tile = 0;
        prev_tile.index = -1;

        last_empty_cell = -1;

        if(params.is_positive)
        {
            for(*iter_j = SIZE - 1; *iter_j >= 0; --*iter_j)
                update_flag |= handle_line_increment(game, params, &prev_tile);

            for(*iter_j = SIZE - 1; *iter_j >= 0; --*iter_j)
                update_flag |= handle_line_order(game, params, &last_empty_cell);
        }
        else
        {
            for(*iter_j = 0; *iter_j < SIZE; ++*iter_j)
                update_flag |= handle_line_increment(game, params, &prev_tile);

            for(*iter_j = 0; *iter_j < SIZE; ++*iter_j)
                update_flag |= handle_line_order(game, params, &last_empty_cell);
        }
    }

    return update_flag;
}

bool handle_line_increment(struct game *game, struct line_handle_params params, struct prev_tile_info *prev_tile)
{
    char tile = tile_at(game, params);
    if(tile == ' ')
        return false;
    
    if(tile != prev_tile->tile)
    {
        prev_tile->tile = tile;
        prev_tile->index = get_dim_coord(params);
        return false;
    }

    tile_at(game, params) = incrementTile(tile, &game->score);

    tile_at_index(game, params, prev_tile->index) = ' ';

    prev_tile->tile = 0;

    return true;
}

bool handle_line_order(struct game *game, struct line_handle_params params, int *last_empty_cell)
{
    char tile = tile_at(game, params);
    if(tile == ' ')
    {
        if(*last_empty_cell < 0)
            *last_empty_cell = get_dim_coord(params);
        return false;
    }

    if(*last_empty_cell < 0)
        return false;

    while(tile_at_index(game, params, *last_empty_cell) != ' ')
    {
        handle_last_empty_cell(params, last_empty_cell);
        if(*last_empty_cell < 0 || *last_empty_cell >= SIZE)
            return false;
    }

    tile_at_index(game, params, handle_last_empty_cell(params, last_empty_cell)) = tile_at(game, params);
    
    tile_at(game, params) = ' ';

    return true;
}

char* _tile_at_index(struct game *game, struct line_handle_params params, int index)
{
    if(params.is_horizontal)
        return &game->board[params.row][index];
    return &game->board[index][params.col];
}

char incrementTile(char tile, int *score)
{
    *score += 1 << (tile - 'A' + 2);
    return tile + 1;
}