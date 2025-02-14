#ifndef _PLAYFAIR_H
#define _PLAYFAIR_H

#define ALPHA "ABCDEFGHIJKLMNOPQRSTUVXYZ"

/**
 * Function for encrypting the given plaintext by applying the Playfair cipher.
 *
 * @param key - Reference to a string representing the key which will be used for encrypting the plaintext.
 * The key is represented by a single case-insensitive word consisting of only alphabetical characters.
 * The individual letters in this key cannot repeat
 * (if they do, the implementation of this function must ensure that the duplicates are removed).
 * @param text - Reference to a string representing the plaintext to be encrypted.
 * This text can consist of case-insensitive letters or the space character ' '.
 * No other characters are allowed (they cannot be encrypted).
 * @return reference to the ciphertext produced by encryption, or NULL if the encryption was not successful.
 */
char* playfair_encrypt(const char* key, const char* text);


/**
 * Function for decrypting the given ciphertext by applying the Playfair cipher.
 *
 * @param key - Reference to a string representing the key which has been used for encrypting the ciphertext.
 * The key is represented by a single case-insensitive word consisting of only alphabetical characters.
 * @param text - Reference to a string representing the ciphertext to be decrypted.
 * @return reference to the plaintext produced by decryption, or NULL if the decryption was not successful.
 */
char* playfair_decrypt(const char* key, const char* text);

#endif
