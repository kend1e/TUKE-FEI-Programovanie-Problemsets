#ifndef COMMAND_H
#define COMMAND_H

#include <regex.h>

/**
 * Struct defining command
 *
 * Note that name and description are expected to be allocated on the heap,
 * and they should be freed on command destruction.
 */
struct command{
    char*   name;           /// command name, must be unique
    char*   description;    /// command description
    regex_t preg;           /// precompiled pattern buffer
    size_t  nmatch;         /// number of matches
    char**  groups;         /// matched groups
};


/**
 * Creates command with name and description
 *
 * This function creates new command. Every command is defined with at least
 * it's name and description. For better recognition of command and it's
 * parameters you can specify search pattern as regular expression following with
 * the number of groups to match. If you specify the search pattern for your
 * command, you can easy specify several forms of typing the same command.
 * Function returns reference to the newly created command, or NULL, if command
 * could not be created.
 * @param name command name
 * @param description command description for usage with HELP command
 * @param pattern search pattern for regular expression
 * @param nmatch the number of groups which can be matched with regexp usage
 * @return The reference of the command in memory or NULL, if command could not be created or name or description were not provided.
 */
struct command* create_command(char* name, char* description, char* pattern, size_t nmatch);


/**
 * Destroys command
 *
 * Destroys (frees) command and all of its resources.
 * @param command command to be destroyed
 * @return Always returns NULL.
 */
struct command* destroy_command(struct command* command);

#endif
