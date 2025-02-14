#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "bmp.h"

char* vigenere_handle(const char* key, const char* text, bool encrypt);

unsigned char* bit_handle(const unsigned char* text, bool encrypt);
unsigned char bit_handle_char(const unsigned char letter, bool encrypt);

char* reverse(const char* text)
{
    if(text == NULL)
        return NULL;

    int text_len = strlen(text);
    char *output = malloc((text_len + 1) * sizeof(char));

    for(int i = 0; i < text_len; ++i)
        output[i] = toupper(text[text_len - i - 1]);

    output[text_len] = 0;
        
    return output;
}

char* vigenere_encrypt(const char* key, const char* text)
{
    return vigenere_handle(key, text, true);
}

char* vigenere_decrypt(const char* key, const char* text)
{
    return vigenere_handle(key, text, false);
}

unsigned char* bit_encrypt(const char* text)
{
    return bit_handle((unsigned char*) text, true);
}

char* bit_decrypt(const unsigned char* text)
{
    return (char*) bit_handle(text, false);
}

unsigned char* bmp_encrypt(const char* key, const char* text)
{
    char *reversed = reverse(text);
    char *vigenere = vigenere_encrypt(key, reversed);
    unsigned char *result = bit_encrypt(vigenere);

    free(reversed);
    free(vigenere);

    return result;
}

char* bmp_decrypt(const char* key, const unsigned char* text)
{
    char *decrypted = bit_decrypt(text);
    char *vigenere = vigenere_decrypt(key, decrypted);
    char *result = reverse(vigenere);

    free(decrypted);
    free(vigenere);

    return result;
}

char* vigenere_handle(const char* key, const char* text, bool encrypt)
{
    if(key == NULL || text == NULL)
        return NULL;

    int key_len = strlen(key);
    int text_len = strlen(text);
    char *output = malloc((text_len + 1) * sizeof(char));

    int key_read_pos = 0;
    int output_write_pos = 0;

    for(int i = 0; i < text_len; ++i)
    {
        char letter = toupper(text[i]);
        char letter_out;

        if(letter >= 'A' && letter <= 'Z')
        {
            char letter_key = toupper(key[key_read_pos++]);

            if(key_read_pos >= key_len)
                key_read_pos = 0;

            if(letter_key < 'A' || letter_key > 'Z')
            {
                free(output);
                return NULL;
            }
                
            letter_out = letter + (letter_key - 'A') * (encrypt ? 1 : -1);

            if(letter_out > 'Z')
                letter_out += ('A' - 'Z' - 1);
            else if(letter_out < 'A')
                letter_out += (-'A' + 'Z' + 1);
        }
        else
            letter_out = letter;
        
        output[output_write_pos++] = letter_out;
    }
    output[text_len] = 0;

    return output;
}

unsigned char* bit_handle(const unsigned char* text, bool encrypt)
{
    if(text == NULL)
        return NULL;

    int text_len = strlen((char*) text);
    unsigned char* output = malloc((text_len + 1) * sizeof(unsigned char));

    for(int i = 0; i < text_len; ++i)
        output[i] = bit_handle_char(text[i], encrypt);

    output[text_len] = 0;
    
    return output;
}

unsigned char bit_handle_char(const unsigned char letter, bool encrypt)
{
    unsigned char result = 0;

    result |= (letter & 128) >> 1;
    result |= (letter & 64) << 1;

    result |= (letter & 32) >> 1;
    result |= (letter & 16) << 1;

    result |= (letter & 15) ^ ((encrypt ? result : letter) >> 4);

    return result;
}
