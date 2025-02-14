#ifndef ROOM_H
#define ROOM_H

#include "item.h"
#include "container.h"

/**
 * Structure representing game location
 *
 * Note that name and description are expected to be allocated on the heap,
 * and they should be freed on room destruction.
 */
struct room {
    char* name;                 /// name of the room/location
    char* description;          /// description of the room/location
    struct room *north;         /// reference to the room on north
    struct room *south;         /// reference to the room on south
    struct room *east;          /// reference to the room on east
    struct room *west;          /// reference to the room on west
    struct container* items;    /// list of items in the room/location
};


/**
 * Creates new room
 *
 * Room is created with name and description. Both parameters are mandatory. If
 * one of them is not present, room can't be created.
 * @param name room name
 * @param description room description
 * @return The reference to the newly created room or NULL, if room could not be created.
 */
struct room* create_room(char *name, char *description);


/**
 * Destroys room
 *
 * This function frees all the memory used for room creation and returns NULL
 * as new room reference.
 * @param room room to destroy
 * @return Always returns NULL
 */
struct room* destroy_room(struct room* room);


/**
 * Sets the exits for given room
 *
 * From each room exist exits to four different directions: north, south, east and west.
 * If you want to connect given room with another one, just pass reference to that room in
 * specific direction. If there is no such room for given direction, pass NULL.
 * @param room room, which exits you want to set
 * @param north reference to the room on north from given room
 * @param south reference to the room on south from given room
 * @param east  reference to the room on east from given room
 * @param west reference to the room on west from given room
 */
void set_exits_from_room(struct room *room, struct room *north, struct room *south, struct room *east, struct room *west);


/**
 * Prints content of the room
 * @param room the requested room to show info about
 */
void show_room(const struct room* room);


/**
 * Deletes item from the room
 *
 * Function deletes item in the room based on it's pointer. If there is no such
 * item in the room, nothing will happen.
 * Function doesn't destroy item. It only removes the item from the room's list
 * of items.
 * @param room where to search
 * @param item pointer to the item to delete from room
 */
void delete_item_from_room(struct room* room, struct item* item);


/**
 * Add item to room
 *
 * Function adds an item specified by it's reference to the list of items of
 * given room. The item could be added in no particular order.
 */
void add_item_to_room(struct room* room, struct item* item);


/**
 * Search for the item in the room
 *
 * Finds and returns a pointer to the item in the room identified by it's name
 * Name is case insensitive. If such item doesn't exist in the room, NULL is
 * returned. The item itself remains in the room.
 * @param room where to search
 * @param name name of item to search for
 * @return Returns reference to the found item or NULL if item was not found.
 */
struct item* get_item_from_room(const struct room* room, const char* name);

#endif
