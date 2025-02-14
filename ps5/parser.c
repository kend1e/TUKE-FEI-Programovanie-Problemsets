#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "parser.h"

void register_command(struct parser *parser, char* name, char* description, char* pattern, size_t nmatch);

struct parser* create_parser()
{
    struct parser *parser = calloc(1, sizeof(struct parser));

    register_command(parser, "KONIEC",
        "Príkaz ukončí rozohratú hru. Nastaví príslušný stav hry.", "(KONIEC|EXIT)", 2);
    register_command(parser, "SEVER",
        "Presun do miestnosti nachádzajúcej sa na sever od aktuálnej. Zmení referenciu aktuálnej miestnosti.", "(SEVER|S)", 2);
    register_command(parser, "JUH",
        "Presun do miestnosti nachádzajúcej sa na juh od aktuálnej. Zmení referenciu aktuálnej miestnosti.", "(JUH|J)", 2);
    register_command(parser, "VYCHOD",
        "Presun do miestnosti nachádzajúcej sa na východ od aktuálnej. Zmení referenciu aktuálnej miestnosti.", "(VYCHOD|V)", 2);
    register_command(parser, "ZAPAD",
        "Presun do miestnosti nachádzajúcej sa na západ od aktuálnej. Zmení referenciu aktuálnej miestnosti.", "(ZAPAD|Z)", 2);
    register_command(parser, "ROZHLIADNI SA",
        "Príkaz vypíše aktuálne informácie o miestnosti, v ktorej sa hráč práve nachádza.", "(ROZHLIADNI SA)", 1);
    register_command(parser, "PRIKAZY",
        "Príkaz vypíše na obrazovku zoznam všetkých príkazov, ktoré hra poskytuje.", "(PRIKAZY|HELP|POMOC)", 3);
    register_command(parser, "VERZIA",
        "Príkaz zobrazí číslo verzie hry, ľubovoľný sprievodný text a meno a priezvisko autora s kontaktom (e-mailová adresa, webová stránka).", "(VERZIA)", 1);
    register_command(parser, "RESTART",
        "Znovu spustí hru od začiatku. Zmení stav hry na požadovaný.", "(RESTART)", 1);
    register_command(parser, "O HRE",
        "Príkaz zobrazí krátky text, ktorý poslúži ako úvod do príbehu. Ako dobrý začiatok sa javí známy text: Kde bolo tam bolo, …", "(O HRE|ABOUT)", 2);
    register_command(parser, "VEZMI",
        "Vloží predmet z miestnosti do batohu. Príkaz má jeden povinný parameter, ktorým je názov predmetu. Ak predmet nebude zadaný, program vypíše na obrazovku vhodnú hlášku (napr. Neviem, čo chceš vziať.).", "(VEZMI)", 1);
    register_command(parser, "POLOZ",
        "Položí predmet z batohu do miestnosti. Príkaz má jeden povinný parameter, ktorým je názov predmetu. Ak predmet nebude zadaný, program vypíše na obrazovku vhodnú hlášku (napr. Neviem, čo chceš položiť.)", "(POLOZ)", 1);
    register_command(parser, "INVENTAR",
        "Zobrazí obsah hráčovho batohu.", "(INVENTAR|I)", 2);
    register_command(parser, "POUZI",
        "Použije predmet z batohu alebo miestnosti. Príkaz má jeden povinný parameter, ktorým je názov predmetu. Ak predmet nebude zadaný, program vypíše na obrazovku vhodnú hlášku (napr. Neviem, čo chceš použiť.).", "(POUZI)", 1);
    register_command(parser, "PRESKUMAJ",
        "Vypíše opis predmetu, ktorý sa musí nachádzať v miestnosti alebo batohu. Príkaz má jeden povinný parameter, ktorým je názov predmetu. Ak predmet nebude zadaný alebo sa nenájde v batohu alebo v miestnosti, program vypíše na obrazovku vhodnú hlášku (napr. Neviem, čo chceš preskúmať.).", "(PRESKUMAJ)", 1);
    register_command(parser, "NAHRAJ",
        "Príkaz zabezpečí nahratie uloženej pozície hry z disku. Voliteľným parametrom je cesta k súboru.", "(NAHRAJ|LOAD)", 2);
    register_command(parser, "ULOZ",
        "Príkaz uloží stav rozohratej hry na disk. Voliteľným parametrom je cesta k súboru.", "(ULOZ|SAVE)", 2);

    return parser;
}

struct parser* destroy_parser(struct parser* parser)
{
    if(parser == NULL)
        return NULL;
    
    parser->commands = destroy_containers(parser->commands);
    parser->history = destroy_containers(parser->history);

    free(parser);

    return NULL;
}

struct command* parse_input(struct parser* parser, char* input)
{
    if(parser == NULL || input == NULL)
        return NULL;

    struct container *c_next = parser->commands;
    while(c_next != NULL)
    {
        if(!strcasecmp(c_next->command->name, input))
            return c_next->command;

        regmatch_t matches[c_next->command->nmatch];
        
        if(c_next->command->nmatch > 0 && !regexec(&c_next->command->preg, input, c_next->command->nmatch, matches, 0))
            return c_next->command;
        
        c_next = c_next->next;
    }

    return NULL;
}

void register_command(struct parser *parser, char* name, char* description, char* pattern, size_t nmatch)
{
    const char *pattern_prefix = "^\\s*";
    const char *pattern_suffix = "\\s*$";

    size_t prefix_len = strlen(pattern_prefix);
    size_t suffix_len = strlen(pattern_suffix);
    size_t pattern_len = strlen(pattern);

    char *pattern_mod = calloc(1, pattern_len + prefix_len + suffix_len + 1);
    strcpy(pattern_mod, pattern_prefix);
    strcpy(pattern_mod + prefix_len, pattern);
    strcpy(pattern_mod + prefix_len + pattern_len, pattern_suffix);

    struct command *command = create_command(name, description, pattern_mod, nmatch);
    struct container *container = create_container(parser->commands, COMMAND, command);
    if(parser->commands == NULL)
        parser->commands = container;

    free(pattern_mod);
}