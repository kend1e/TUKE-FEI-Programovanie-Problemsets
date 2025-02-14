#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "hof.h"

#define MAX_PLAYER_COUNT 10

int load(struct player list[])
{
    FILE *file = fopen(HOF_FILE, "r");
    if(file == NULL)
        return -1;

    int scan_res;
    struct player player;
    int size = 0;

    while(size < MAX_PLAYER_COUNT &&
        (scan_res = fscanf(file, "%s %d", player.name, &player.score)) != EOF)
    {
        if(scan_res != 2)
        {
            fclose(file);
            return -1;
        }

        add_player(list, &size, player);
    }

    fclose(file);

    return size;
}

bool save(const struct player list[], const int size)
{
    FILE *file = fopen(HOF_FILE, "w");
    if(file == NULL)
        return false;

    for(int i = 0; i < size; ++i)
        fprintf(file, "%s %d\n", list[i].name, list[i].score);

    fclose(file);

    return true;
}

bool add_player(struct player list[], int* size, const struct player player)
{
    if(*size == 0)
    {
        list[(*size)++] = player;
        return true;
    }

    bool is_on_top = false;
    for(int i = *size - 1; i >= 0; --i)
    {
        is_on_top = false;

        if(list[i].score < player.score)
        {
            if(i == 0)
                is_on_top = true;
            else
                continue;
        }
        else if(i == 0 && list[i].score == player.score)
            is_on_top = true;

        if(i == *size - 1 && *size >= MAX_PLAYER_COUNT)
            return false;

        if(!is_on_top && (is_on_top = list[i].score == player.score) && i > 0 && list[i - 1].score == player.score)
            continue;

        int write_pos = is_on_top ? i : (i + 1);

        for(int j = *size - 1; j >= write_pos; --j)
            if(j + 1 < MAX_PLAYER_COUNT)
                list[j + 1] = list[j];

        list[write_pos] = player;
        if(*size < MAX_PLAYER_COUNT)
            (*size)++;

        break;
    }

    return true;
}