#ifndef BACKPACK_H
#define BACKPACK_H

#include <stdbool.h>

#include "item.h"
#include "container.h"

/**
 * Structure representing the backpack
 */
struct backpack {
    int capacity;               /// backpack capacity (max nr. of items)
    int size;                   /// current size
    struct container* items;    /// list of items
};


/**
 * Creates backpack
 * @param capacity backpack capacity
 * @return Reference to created backpack.
 */
struct backpack* create_backpack(const int capacity);


/**
 * Destroys backpack
 * @param backpack backpack to destroy
 * @return Always returns NULL.
 */
struct backpack* destroy_backpack(struct backpack* backpack);


/**
 * Adds item to backpack
 * @param backpack
 * @param item
 * @return true, if item was added successfully, false otherwise (backpack is full)
 */
bool add_item_to_backpack(struct backpack* backpack, struct item* item);


/**
 * Deletes given item from backpack
 * @param backpack backpack, from which the item will be deleted
 * @param item item to delete
 */
void delete_item_from_backpack(struct backpack* backpack, struct item* item);


/**
 * Gets the item by name
 * @param bakcpack backpack to seaerch for item
 * @param name name of item to get
 * @return Reference to the item, if found, NULL otherwise.
 */
struct item* get_item_from_backpack(const struct backpack* backpack, char* name);

#endif
