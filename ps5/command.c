#include <stdlib.h>
#include <regex.h>
#include <string.h>

#include "command.h"

struct command* create_command(char* name, char* description, char* pattern, size_t nmatch)
{
    if(name == NULL || name[0] == 0 || description == NULL || description[0] == 0)
        return NULL;

    struct command *command = calloc(1, sizeof(struct command));

    if(pattern != NULL)
        command->nmatch = nmatch;

    if(command->nmatch > 0 && regcomp(&command->preg, pattern, REG_EXTENDED | REG_ICASE) != 0)
    {
        free(command);
        return NULL;
    }

    command->name = malloc(strlen(name) + 1);
    command->description = malloc(strlen(description) + 1);
    strcpy(command->name, name);
    strcpy(command->description, description);
    
    return command;
}

struct command* destroy_command(struct command* command)
{
    if(command == NULL)
        return NULL;

    free(command->name);
    free(command->description);

    if(command->nmatch > 0)
        regfree(&command->preg);
    free(command);
    
    return NULL;
}