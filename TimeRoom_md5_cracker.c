#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/md5.h>

#define MAX_WORDS 10000
#define MAX_WORD_LENGTH 256
#define MAX_HASHES 10000
#define MAX_HASH_LENGTH 33  // MD5 hash is 32 characters plus null terminator

// ANSI color codes
#define RESET       "\x1b[0m"
#define GREEN       "\x1b[32m"
#define BLUE        "\x1b[34m"
#define YELLOW      "\x1b[33m"
#define WHITE       "\x1b[37m"

// Function to load wordlist from a file
int load_wordlist(const char *filename, char words[MAX_WORDS][MAX_WORD_LENGTH]) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file: %s\n", filename);
        return -1;
    }

    int i = 0;
    while (fgets(words[i], MAX_WORD_LENGTH, file)) {
        words[i][strcspn(words[i], "\n")] = 0;  // Remove newline character
        i++;
        if (i >= MAX_WORDS) break;  // Prevent overflow
    }

    fclose(file);
    return i;  // Return number of words loaded
}

// Function to load hashlist from a file
int load_hashlist(const char *filename, char hashes[MAX_HASHES][MAX_HASH_LENGTH]) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file: %s\n", filename);
        return -1;
    }

    int i = 0;
    while (fgets(hashes[i], MAX_HASH_LENGTH, file)) {
        hashes[i][strcspn(hashes[i], "\n")] = 0;  // Remove newline character
        i++;
        if (i >= MAX_HASHES) break;  // Prevent overflow
    }

    fclose(file);
    return i;  // Return number of hashes loaded
}

// Function to calculate MD5 hash of a string
void md5_decrypt(const char *word, unsigned char *digest) {
    MD5_CTX context;
    MD5_Init(&context);
    MD5_Update(&context, (unsigned char*)word, strlen(word));
    MD5_Final(digest, &context);
}

// Function to convert MD5 digest to a hex string
void md5_to_hex(unsigned char *digest, char *output) {
    for (int i = 0; i < MD5_DIGEST_LENGTH; i++) {
        sprintf(&output[i * 2], "%02x", digest[i]);
    }
    output[MD5_DIGEST_LENGTH * 2] = '\0';  // Null-terminate the string
}

// Main function for cracking
int main(int argc, char *argv[]) {
    if (argc != 5) {
        printf(WHITE "Usage: %s -H <hashfile> -P <passwordfile>\n" RESET, argv[0]);
        return 1;
    }

    char hashes[MAX_HASHES][MAX_HASH_LENGTH];
    char words[MAX_WORDS][MAX_WORD_LENGTH];
    unsigned char digest[MD5_DIGEST_LENGTH];
    char generated_hash[MAX_HASH_LENGTH];
    int hash_count, word_count;

    // Load hashlist and wordlist
    printf(BLUE "Loading files...\n" RESET);
    hash_count = load_hashlist(argv[2], hashes);
    word_count = load_wordlist(argv[4], words);

    if (hash_count < 0 || word_count < 0) {
        return 1;  // Error in loading files
    }

    // Start cracking
    printf(BLUE "Cracking started...\n" RESET);
    for (int i = 0; i < hash_count; i++) {
        for (int j = 0; j < word_count; j++) {
            md5_decrypt(words[j], digest);

            // Convert digest to hex string
            md5_to_hex(digest, generated_hash);

            // Compare the generated hash with the target hash
            if (strncmp(generated_hash, hashes[i], MD5_DIGEST_LENGTH * 2) == 0) {
                printf(GREEN "Match found: Hash '%s' cracked with password '%s'\n" RESET, hashes[i], words[j]);
                break;  // Once a match is found, continue to the next hash
            }
        }
    }

    printf(GREEN "Cracking completed.\n" RESET);
    return 0;
}
