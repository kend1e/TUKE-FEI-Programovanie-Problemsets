#include <stdlib.h>
#include <strings.h>

#include "game.h"
#include "world.h"

void play_game(struct game* game)
{
    if(game == NULL)
        return;

    struct item *i_keycard = get_item_from_room(game->current_room, "Keycard");

    add_item_to_backpack(game->backpack, i_keycard);
    get_item_from_backpack(game->backpack, "Keycard");

    delete_item_from_backpack(game->backpack, i_keycard);
    delete_item_from_room(game->current_room, i_keycard);
    destroy_item(i_keycard);

    struct command *command = parse_input(game->parser, "RESTART");
    execute_command(game, command);


    struct room *room = get_room(game->world, "Airlock");
    show_room(room);
}

struct game* create_game()
{
    struct game *game = calloc(1, sizeof(struct game));

    game->state = PLAYING;
    game->parser = create_parser();
    game->world = create_world();
    game->backpack = create_backpack(5);

    game->current_room = game->world->room;

    return game;
}

struct game* destroy_game(struct game* game)
{
    if(game == NULL)
        return NULL;

    destroy_parser(game->parser);
    destroy_world(game->world);
    destroy_backpack(game->backpack);

    free(game);

    return NULL;
}

void execute_command(struct game* game, struct command* command)
{
    if(game == NULL || command == NULL)
        return;

    if(!strcasecmp(command->name, "KONIEC"))
    {
        game->state = GAMEOVER;
        return;
    }

    if(!strcasecmp(command->name, "SEVER"))
    {
        if(game->current_room->north != NULL)
            game->current_room = game->current_room->north;
        return;
    }

    if(!strcasecmp(command->name, "JUH"))
    {
        if(game->current_room->south != NULL)
            game->current_room = game->current_room->south;
        return;
    }

    if(!strcasecmp(command->name, "VYCHOD"))
    {
        if(game->current_room->east != NULL)
            game->current_room = game->current_room->east;
        return;
    }

    if(!strcasecmp(command->name, "ZAPAD"))
    {
        if(game->current_room->west != NULL)
            game->current_room = game->current_room->west;
        return;
    }

    if(!strcasecmp(command->name, "ROZHLIADNI SA"))
    {
        show_room(game->current_room);
        return;
    }

    if(!strcasecmp(command->name, "RESTART"))
    {
        game->state = RESTART;
        return;
    }
}