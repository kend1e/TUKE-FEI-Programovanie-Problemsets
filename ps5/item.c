#include <stdlib.h>
#include <string.h>

#include "item.h"

struct item* create_item(char* name, char* description, unsigned int properties)
{
    if(name == NULL || name[0] == 0 || description == NULL || description[0] == 0)
        return NULL;

    struct item *item = calloc(1, sizeof(struct item));

    item->name = malloc(strlen(name) + 1);
    item->description = malloc(strlen(description) + 1);;
    item->properties = properties;

    strcpy(item->name, name);
    strcpy(item->description, description);

    return item;
}

struct item* destroy_item(struct item* item)
{
    if(item == NULL)
        return NULL;

    free(item->name);
    free(item->description);
    free(item);
    
    return NULL;
}