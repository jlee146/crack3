#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>

#include "md5.h"

#if __has_include("fileutil.h")
#include "fileutil.h"
#endif

#define PASS_LEN 50     // Maximum length any password will be.
#define HASH_LEN 33     // Length of hash plus one for null.


int main(int argc, char *argv[])
{
    if (argc < 3) 
    {
        printf("Usage: %s hash_file dictionary_file\n", argv[0]);
        exit(1);
    }

    // TODO: Read the hashes file into an array.
    //   Use either a 2D array or an array of arrays.
    //   Use the loadFile function from fileutil.c
    int size;
    char **hashes = loadFileAA(argv[1], &size);
    
    // TODO
    // Open the password file for reading.
    FILE *passwordFile = fopen(argv[2], "r");
    if (!passwordFile)
    {
        printf("Error loading password file\nProgram exiting\n");
        exit(1);
    }

    // TODO
    // For each password, hash it, then use the array search
    // function from fileutil.h to find the hash.
    int count = 0;
    char passwords[PASS_LEN];
    while (fgets(passwords, sizeof(passwords), passwordFile))
    {
        // Trim newline
        passwords[strcspn(passwords, "\n")] = 0;

        // Actually has the password
        char *hashedPassword = md5(passwords, strlen(passwords));

        // Search for the password
        char *found = substringSearchAA(hashedPassword, hashes, size);

        // If you find it, display the password and the hash.
        if (found)
        {
            printf("%s : %s", passwords, found);
         
            // Keep track of how many hashes were found.
            count++;
        }

    }

    // TODO
    // When done with the file:
    //   Close the file
    fclose(passwordFile);

    //   Display the number of hashes found.
    printf("Found: %d\n", count);

    //   Free up memory.
    freeAA(hashes, size);

    return 0;
}
