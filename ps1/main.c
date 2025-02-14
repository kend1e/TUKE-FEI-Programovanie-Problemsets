#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "playfair.h"
#include "bmp.h"

int main()
{
    unsigned char *bmp_encrypted;
    char *bmp_decrypted;

    bmp_encrypted = bmp_encrypt("Test", "THIS IS ENCRYPTION TEST");
    bmp_decrypted = bmp_decrypt("Test", bmp_encrypted);

    printf("%s\n", bmp_decrypted);

    free(bmp_encrypted);
    free(bmp_decrypted);

    //---

    char *playfair_encrypted, *playfair_decrypted;

    playfair_encrypted = playfair_encrypt("Test", "THIS IS ENCRYPTION TEST");
    playfair_decrypted = playfair_decrypt("Test", playfair_encrypted);

    printf("%s\n", playfair_decrypted);

    free(playfair_encrypted);
    free(playfair_decrypted);

    return 0;
}