#include <stdlib.h>

#include "backpack.h"

struct backpack* create_backpack(const int capacity)
{
    struct backpack *backpack = calloc(1, sizeof(struct backpack));

    backpack->capacity = capacity;
    backpack->size = 0;

    return backpack;
}

struct backpack* destroy_backpack(struct backpack* backpack)
{
    if(backpack == NULL)
        return NULL;

    destroy_containers(backpack->items);

    free(backpack);

    return NULL;
}

bool add_item_to_backpack(struct backpack* backpack, struct item* item)
{
    if(backpack == NULL || item == NULL)
        return false;

    if(backpack->size >= backpack->capacity)
        return false;

    struct container *container = create_container(backpack->items, ITEM, item);

    if(backpack->items == NULL)
        backpack->items = container;

    backpack->size++;

    return true;
}

void delete_item_from_backpack(struct backpack* backpack, struct item* item)
{
    if(backpack == NULL || item == NULL)
        return;

    backpack->items = remove_container(backpack->items, item);

    backpack->size--;
}

struct item* get_item_from_backpack(const struct backpack* backpack, char* name)
{
    if(backpack == NULL)
        return NULL;
    
    return get_from_container_by_name(backpack->items, name);
}