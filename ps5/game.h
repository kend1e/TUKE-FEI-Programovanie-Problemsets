#ifndef GAME_H
#define GAME_H

#include "room.h"
#include "command.h"
#include "backpack.h"
#include "parser.h"
#include "container.h"

/// Max. size of input buffer (line)
#define INPUT_BUFFER_SIZE 100

/**
 * Available game states
 */
enum gamestate {
    GAMEOVER,       // player died or typed command for quit
    PLAYING,        // game is still playing
    SOLVED,         // game has been solved
    RESTART         // request for game restart was given
};


/**
 * Game context structure
 */
struct game{
    enum gamestate      state;          /// game state
    struct parser*      parser;         /// command line parser
    struct container*   world;          /// list of all rooms
    struct room*        current_room;   /// reference to the current room
    struct backpack*    backpack;       /// player's backpack
};


/**
 * Starts game loop for the given game
 *
 * Main function of the game, which contains the game loop. So it's
 * responsible for reading the input from player, updating the state
 * of game and rendering the new situation.
 * @param game the game to be played
 */
void play_game(struct game* game);


/**
 * Creates game
 *
 * Function creates game structure and returns it's reference.
 * But it will create not only the game structure, but also
 * initializes and creates all of it's members.
 * @return The created game object or NULL, if game could not be created.
 */
struct game* create_game();


/**
 * Destroys game
 *
 * Destroys the game structure. With the destroying the game function
 * destroys also all of it's members. This function should be called
 * as the last, when the game is going to quit.
 * Function always returns NULL references as the new reference to
 * the game structure.
 * @param game the game to be destroyed
 * @return Always returns NULL
 */
struct game* destroy_game(struct game* game);


/**
 * Executes command in the game
 *
 * Function executes the command given as the function parameter
 * on the game object. It doesn't return any value, but updates the
 * state of the game.
 * This function can be considered as the main function, which
 * contains the game logic.
 * @param game the game
 * @param command the command to be executed
 */
void execute_command(struct game* game, struct command* command);

#endif
