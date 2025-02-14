#ifndef _HOF_H
#define _HOF_H

#include <stdbool.h>

// name of the Hall of Fame score file
#define HOF_FILE "score"

// the delimiter used in score file
#define DELIMITER " "

struct player{
    // name of the player (avoid usage of spaces in name)
    char name[30];
    // player's score
    int score;
};


/**
 * Loads hall of fame from file
 * Function loads hall of fame list from file, which name is defined in macro HOF_FILE.
 * List is loaded to the given output parameter list. Function returns the size of loaded list -
 * if file contains more than 10 entries, only first 10 entries will be loaded.
 * @param list the list of players
 * @return the number of loaded entries or -1, if there was error in loading
 */
int load(struct player list[]);


/**
 * Saves the hall of fame list to the file
 * Function saves hall of fame list to the file, which name is defined in macro HOF_FILE.
 * Function saves max. 10 entries from the given list. If the list was saved successfully,
 * function returns true.
 * @param list the list of players
 * @param size the real size of entries in list
 * @return true, if file was saved successfully, false otherwise
 */
bool save(const struct player list[], const int size);


/**
 * Adds player to the hall of fame
 * Function updates the hall of fame list, if score of given player is higher than last entry of
 * hall of fame list. If the update was successfull, parameters list and size will be updated and
 * function returns true. The list is held in sorted form from the best player (highest score). If
 * score of given player is same as the existing entry, the entries are sorted alphabetically by
 * the names of the players in ascending order.
 * @param list the list of players
 * @param size the size of the list
 * @param player the player to add
 * @return true, if player (entry) was added to the list, false otherwise
 */
bool add_player(struct player list[], int* size, const struct player player);

#endif
