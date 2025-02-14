#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "room.h"

struct room* create_room(char *name, char *description)
{
    if(name == NULL || name[0] == 0 || description == NULL || description[0] == 0)
        return NULL;

    struct room *room = calloc(1, sizeof(struct room));

    room->name = malloc(strlen(name) + 1);
    room->description = malloc(strlen(description) + 1);

    strcpy(room->name, name);
    strcpy(room->description, description);

    return room;
}

struct room* destroy_room(struct room* room)
{
    if(room == NULL)
        return NULL;

    destroy_containers(room->items);

    free(room->name);
    free(room->description);
    free(room);

    return NULL;
}

void set_exits_from_room(struct room *room, struct room *north, struct room *south, struct room *east, struct room *west)
{
    if(room == NULL)
        return;

    room->north = north;
    room->south = south;
    room->east = east;
    room->west = west;
}

void show_room(const struct room* room)
{
    if(room == NULL)
        return;
    
    printf("%s\n", room->description);

    printf("Mozne vychody z miesnosti:\n");

    if(room->north != NULL)
        printf("    sever");
    if(room->south != NULL)
        printf("    juh");
    if(room->east != NULL)
        printf("    vychod");
    if(room->west != NULL)
        printf("    zapad");

    printf("\nVidis:\n");
    
    struct container *c_next = room->items;
    while(c_next != NULL)
    {
        printf("    %s\n", c_next->item->name);
        c_next = c_next->next;
    }
}

void delete_item_from_room(struct room* room, struct item* item)
{
    if(room == NULL || item == NULL)
        return;

    room->items = remove_container(room->items, item);
}

void add_item_to_room(struct room* room, struct item* item)
{
    if(room == NULL || item == NULL)
        return;

    struct container *container = create_container(room->items, ITEM, item);

    if(room->items == NULL)
        room->items = container;
}

struct item* get_item_from_room(const struct room* room, const char* name)
{
    if(room == NULL)
        return NULL;
    
    return get_from_container_by_name(room->items, name);
}