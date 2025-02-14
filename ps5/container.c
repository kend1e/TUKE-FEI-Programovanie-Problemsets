#include <stdlib.h>
#include <strings.h>

#include "container.h"

struct container* destroy_container(struct container* container);

struct container* create_container(struct container* first, enum container_type type, void* entry)
{
    if(entry == NULL || (first != NULL && first->type != type))
        return NULL;

    struct container *c_next = first;
    while(c_next != NULL && c_next->next != NULL)
        c_next = c_next->next;

    struct container *c_new = malloc(sizeof(struct container));

    if(c_next != NULL)
        c_next->next = c_new;

    c_new->next = NULL;
    c_new->type = type;

    switch(type)
    {
    case ROOM:
        c_new->room = (struct room *) entry;
        break;
    case ITEM:
        c_new->item = (struct item *) entry;
        break;
    case COMMAND:
        c_new->command = (struct command *) entry;
        break;
    case TEXT:
        c_new->text = (char *) entry;
        break;
    }

    return c_new;
}

struct container* destroy_containers(struct container* first)
{
    if(first == NULL)
        return NULL;

    struct container *c_next = first;
    while(c_next != NULL)
    {
        struct container *c_temp = c_next->next;

        destroy_container(c_next);
    
        c_next = c_temp;
    }

    return NULL;
}

void* get_from_container_by_name(struct container *first, const char *name)
{
    if(first == NULL || name == NULL || name[0] == 0)
        return NULL;

    struct container *c_next = first;
    while(c_next != NULL)
    {
        char *c_name = NULL;
        void *c_value = NULL;
        switch(c_next->type)
        {
        case ROOM:
            c_name = c_next->room->name;
            c_value = c_next->room;
            break;
        case ITEM:
            c_name = c_next->item->name;
            c_value = c_next->item;
            break;
        case COMMAND:
            c_name = c_next->command->name;
            c_value = c_next->command;
            break;
        case TEXT:
            c_value = c_name = c_next->text;
            break;
        }

        if(c_name != NULL && !strcasecmp(c_name, name))
            return c_value;

        c_next = c_next->next;
    }

    return NULL;
}

struct container* remove_container(struct container *first, void *entry)
{
    if(first == NULL)
        return NULL;

    struct container *c_next = first;
    struct container *c_prev = NULL;
    while(c_next != NULL)
    {
        void *c_value = NULL;
        switch(c_next->type)
        {
        case ROOM:
            c_value = c_next->room;
            break;
        case ITEM:
            c_value = c_next->item;
            break;
        case COMMAND:
            c_value = c_next->command;
            break;
        case TEXT:
            c_value = c_next->text;
            break;
        }

        if(c_value == NULL || c_value == entry)
        {
            struct container *c_temp = c_next->next;

            free(c_next);

            if(c_prev == NULL)
                return c_temp;
            
            c_prev->next = c_temp;
            break;
        }

        c_prev = c_next;
        c_next = c_next->next;
    }

    return first;
}

struct container* destroy_container(struct container* container)
{
    if(container == NULL)
        return NULL;

    switch(container->type)
    {
    case ROOM:
        destroy_room(container->room);
        break;
    case ITEM:
        destroy_item(container->item);
        break;
    case COMMAND:
        destroy_command(container->command);
        break;
    case TEXT:
        free(container->text);
        break;
    }

    free(container);

    return NULL;
}