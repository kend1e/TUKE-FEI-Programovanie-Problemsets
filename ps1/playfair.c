#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include "playfair.h"

#define KEY_ARRAY_SIZE sizeof(ALPHA)
#define KEY_ARRAY_DIM_SIZE 5
#define AUX_CHAR 'X'
#define REPLACED_CHAR_FROM 'W'
#define REPLACED_CHAR_TO 'V'

bool fill_key_array(char key_arr[KEY_ARRAY_SIZE], const char *letter_source);
void pair_handle(const char key_arr[KEY_ARRAY_SIZE], char pair[2], bool encrypt);
void get_coords_from_letter(const char key_arr[KEY_ARRAY_SIZE], const char letter, int coords[2]);
void get_letter_from_coords(const char key_arr[KEY_ARRAY_SIZE], char *letter, const int coords[2]);
void modify_coord(int *coord, int delta);
int find_next_non_empty(const char *text, int text_len, int cur_index);

char* playfair_encrypt(const char* key, const char* text)
{
    if(key == NULL || text == NULL)
        return NULL;

    int text_len = strlen(text);
    char *output = malloc(text_len * 3 * sizeof(char));

    char key_arr[KEY_ARRAY_SIZE] = { 0 };

    if(!fill_key_array(key_arr, key))
    {
        free(output);
        return NULL;
    }
    fill_key_array(key_arr, ALPHA);

    char *output_pair = output;
    for(int i = 0; i < text_len;)
    {
        int next_index_1 = find_next_non_empty(text, text_len, i);
        if(next_index_1 < 0)
            break;
        int next_index_2 = find_next_non_empty(text, text_len, next_index_1 + 1);
        
        output_pair[0] = toupper(text[next_index_1]);
        if(output_pair[0] == REPLACED_CHAR_FROM)
            output_pair[0] = REPLACED_CHAR_TO;

        if(next_index_2 >= 0 && next_index_2 < text_len)
        {
            output_pair[1] = toupper(text[next_index_2]);
            if(output_pair[1] == REPLACED_CHAR_FROM)
                output_pair[1] = REPLACED_CHAR_TO;
            
            if(output_pair[0] == output_pair[1] && output_pair[0] != AUX_CHAR)
            {
                output_pair[1] = AUX_CHAR;
                i = next_index_1 + 1;
            }
            else
                i = next_index_2 + 1;
        }
        else
        {
            output_pair[1] = AUX_CHAR;
            i = next_index_1 + 1;
        }

        pair_handle(key_arr, output_pair, true);

        output_pair[2] = ' ';
        output_pair += 3;
    }

    if(output_pair[-1] == ' ')
        output_pair[-1] = 0;
    else
        output_pair[0] = 0;

    return output;
}

char* playfair_decrypt(const char* key, const char* text)
{
    if(key == NULL || text == NULL)
        return NULL;
    
    int text_len = strlen(text);
    char *output = malloc((text_len + 1) * sizeof(char));

    char key_arr[KEY_ARRAY_SIZE] = { 0 };

    if(!fill_key_array(key_arr, key))
    {
        free(output);
        return NULL;
    }
    fill_key_array(key_arr, ALPHA);

    char *output_pair = output;
    for(int i = 0; i < text_len; i += 3)
    {
        if(i + 1 >= text_len)
            break;
        
        output_pair[0] = toupper(text[i]);
        output_pair[1] = toupper(text[i + 1]);

        if(output_pair[0] == REPLACED_CHAR_FROM || output_pair[1] == REPLACED_CHAR_FROM)
        {
            free(output);
            return NULL;
        }

        pair_handle(key_arr, output_pair, false);

        output_pair += 2;
    }

    output_pair[0] = 0;

    return output;
}

bool fill_key_array(char key_arr[KEY_ARRAY_SIZE], const char *letter_source)
{
    int key_arr_len = strlen(key_arr);
    int source_len = strlen(letter_source);

    bool flag_letter_present;
    for(int i = 0; i < source_len; ++i)
    {
        char letter = toupper(letter_source[i]);

        if(letter < 'A' || letter > 'Z')
        {
            if(letter == ' ')
                continue;
            return false;
        }

        if(letter == REPLACED_CHAR_FROM)
            letter = REPLACED_CHAR_TO;

        flag_letter_present = false;
        for(int j = 0; j < key_arr_len; ++j)
            if(letter == key_arr[j])
            {
                flag_letter_present = true;
                break;
            }

        if(flag_letter_present)
            continue;

        key_arr[key_arr_len++] = letter;

        if(key_arr_len >= KEY_ARRAY_SIZE - 1)
            break;
    }

    if(key_arr_len <= 0)
        return false;

    key_arr[key_arr_len] = 0;
    return true;
}

void pair_handle(const char key_arr[KEY_ARRAY_SIZE], char pair[2], bool encrypt)
{
    int coords[2][2];

    for (int i = 0; i < 2; ++i)
        get_coords_from_letter(key_arr, pair[i], coords[i]);

    if(coords[0][1] == coords[1][1])
    {
        for (int i = 0; i < 2; ++i)
            modify_coord(&coords[i][0], encrypt ? 1 : -1);
    }
    else if(coords[0][0] == coords[1][0])
    {
        for (int i = 0; i < 2; ++i)
            modify_coord(&coords[i][1], encrypt ? 1 : -1);
    }
    else
    {
        int temp = coords[0][1];
        coords[0][1] = coords[1][1];
        coords[1][1] = temp;
    }

    for (int i = 0; i < 2; ++i)
        get_letter_from_coords(key_arr, pair + i, coords[i]);
}

void get_coords_from_letter(const char key_arr[KEY_ARRAY_SIZE], const char letter, int coords[2])
{
    coords[0] = coords[1] = 0;
    for(int i = 0; i < KEY_ARRAY_SIZE; ++i)
        if(key_arr[i] == letter)
        {
            coords[0] = i / KEY_ARRAY_DIM_SIZE;
            coords[1] = i % KEY_ARRAY_DIM_SIZE;
            return;
        }
}

void get_letter_from_coords(const char key_arr[KEY_ARRAY_SIZE], char *letter, const int coords[2])
{
    int index = coords[0] * KEY_ARRAY_DIM_SIZE + coords[1];
    if(index >= 0 && index < KEY_ARRAY_SIZE)
        *letter = key_arr[index];
}

void modify_coord(int *coord, int delta)
{
    int value = *coord + delta;

    if(value >= KEY_ARRAY_DIM_SIZE)
        value -= KEY_ARRAY_DIM_SIZE;
    else if(value < 0)
        value += KEY_ARRAY_DIM_SIZE;

    *coord = value;
}

int find_next_non_empty(const char *text, int text_len, int cur_index)
{
    int index;
    for(index = cur_index; index < text_len; ++index)
        if(text[index] != ' ')
            return index;
    return -1;
}