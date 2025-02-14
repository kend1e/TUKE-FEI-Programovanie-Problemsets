#include <stdlib.h>
#include <strings.h>

#include "world.h"

struct room *register_room(struct container *first, char *name, char *description);

struct container* create_world()
{
    struct room *r_entrance = create_room("Entrance", "Entrance");

    struct container *world = create_container(NULL, ROOM, r_entrance);

    struct room *r_airlock =                register_room(world, "Airlock", "Airlock");
    struct room *r_hallway_1 =              register_room(world, "Hallway - 1", "Hallway - 1");
    struct room *r_hallway_2 =              register_room(world, "Hallway - 2", "Hallway - 2");
    struct room *r_living_quarters =        register_room(world, "Living quarters", "Living quarters");
    struct room *r_kitchen =                register_room(world, "Kitchen", "Kitchen");
    struct room *r_wc =                     register_room(world, "WC", "WC");
    struct room *r_command_center =         register_room(world, "Command center", "Command center");
    struct room *r_missile_silo =           register_room(world, "Missile silo access", "Missile silo access");
    struct room *r_communication_center =   register_room(world, "Communication center", "Communication center");
    struct room *r_infirmary =              register_room(world, "Infirmary", "Infirmary");
    struct room *r_storage =                register_room(world, "Storage", "Storage");
    struct room *r_technical_room  =        register_room(world, "Technical room", "Technical room");
    struct room *r_air =                    register_room(world, "Air purification unit", "Air purification unit");
    struct room *r_water =                  register_room(world, "Water purification unit", "Water purification unit");

    set_exits_from_room(r_entrance, r_airlock, NULL, NULL, NULL);

    set_exits_from_room(r_airlock, r_hallway_1, r_entrance, NULL, NULL);

    set_exits_from_room(r_hallway_1, r_hallway_2, r_airlock, r_command_center, r_living_quarters);

    set_exits_from_room(r_hallway_2, r_storage, r_hallway_1, r_infirmary, r_communication_center);

    set_exits_from_room(r_living_quarters, NULL, r_kitchen, r_hallway_1, r_wc);

    set_exits_from_room(r_kitchen, r_living_quarters, NULL, NULL, NULL);

    set_exits_from_room(r_wc, NULL, r_living_quarters, NULL, NULL);

    set_exits_from_room(r_command_center, NULL, NULL, r_missile_silo, r_hallway_1);

    set_exits_from_room(r_missile_silo, NULL, NULL, NULL, r_command_center);

    set_exits_from_room(r_communication_center, NULL, NULL, r_hallway_2, NULL);

    set_exits_from_room(r_infirmary, NULL, NULL, NULL, r_hallway_2);

    set_exits_from_room(r_storage, NULL, r_hallway_2, NULL, r_technical_room);

    set_exits_from_room(r_technical_room, r_water, NULL, r_storage, r_air);

    set_exits_from_room(r_air, NULL, NULL, r_technical_room, NULL);

    set_exits_from_room(r_water, NULL, r_technical_room, NULL, NULL);

    add_item_to_room(r_entrance, create_item("Keycard", "Keycard", MOVABLE | USABLE));
    add_item_to_room(r_storage, create_item("Filter", "Air filter", MOVABLE | USABLE));
    add_item_to_room(r_wc, create_item("Toothbrush", "Toothbrush", MOVABLE));
    add_item_to_room(r_communication_center, create_item("Paper with codes", "Paper with codes", MOVABLE | EXAMINABLE | USABLE));
    add_item_to_room(r_infirmary, create_item("First aid kit", "First aid kit", MOVABLE | USABLE));
    
    return world;
}

struct room *register_room(struct container *world, char *name, char *description)
{
    struct room *room = create_room(name, description);

    if(!add_room_to_world(world, room))
    {
        free(room);
        return NULL;
    }

    return room;
}

struct container* add_room_to_world(struct container* world, struct room* room)
{
    if(room == NULL)
        return NULL;

    struct container *c_next = world;
    while(c_next != NULL)
    {
        if(!strcasecmp(c_next->room->name, room->name))
            return NULL;
        
        c_next = c_next->next;
    }

   return create_container(world, ROOM, room);
}

struct container* destroy_world(struct container* world)
{
    return destroy_containers(world);
}

struct room* get_room(struct container* world, char* name)
{
    return get_from_container_by_name(world, name);
}