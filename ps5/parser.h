#ifndef PARSER_H
#define PARSER_H

#include "command.h"
#include "container.h"

/**
 * Structure defining parser
 *
 * Parser contains only two members: list of all commands, which
 * parser understands and history of commands, there were typed.
 */
struct parser {
    struct container*   history;    /// list of command line history
    struct container*   commands;   /// list of known commands
};


/**
 * Creates parser
 *
 * Function creates parser structure and returns it's reference or
 * NULL, if the structure could not be created. Function also
 * creates the list of commands, which parser understands.
 * @return Reference to the newly created parser or NULL.
 */
struct parser* create_parser();


/**
 * Destroys the given parser
 *
 * This function is responsible for destroying given parser and
 * releases all of its resources including all it's members.
 * Function returns NULL as the new reference to the parser structure.
 * @param parser the parser to be destroyed
 * @return Always returns NULL.
 */
struct parser* destroy_parser(struct parser* parser);


/**
 * Parses user input
 *
 * Function returns reference to the recognized command from the
 * user's input. If the parsering was not successful, function
 * returns NULL.
 * Parsing is not case sensitive, so the commands "Examine" and
 * "eXaMiNe" are same.
 * Parser is also resistant to the additional white characters.
 * So the input "    examine   chest   " parser examines correctly.
 * @param parser the parser
 * @param input string representing user's input
 * @return The reference to the recognized command or NULL, if input was not recognized successfully.
 */
struct command* parse_input(struct parser* parser, char* input);

#endif
