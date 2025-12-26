#include "files.h"


/*
 * palindromeSensor - Checks if the given string is palindrome
 * @buffer: the string to check
 * Return: 1 if palindrome, else 0
 */
int palindromeSensor(char buffer[]) {
    // If the string is empty return 0
    if (strlen(buffer) <= 0)
        return 0;
    int i = 0, len = strlen(buffer);
    int j = len - 1;

    // Iterate through the string from both sides, and compare each character
    for (; i < len / 2; i++, j--) {
        // If we find a mismatch then it can't be a palindrome
        if (buffer[i] != buffer[j])
            return 0;
    }
    // If we don't find a mismatch, then it must be palindrome
    return 1;
}


/*
 * detectPalindromes - Detects all palindrome words in the given file and prints them
 * @fileName: the name of the file
 * Return: (void)
 */
void detectPalindromes(char fileName[]) {
    // Open the file in read mode
    FILE *filePtr = fopen(fileName, "r");
    if (!filePtr) {
        perror("Fatal: Can't open File: ");
        exit(1);
    }
    
    char buffer[1024]; 
    int buffIndex = 0, currentChar = 0;

    // Iterate through the file character by character and fill the buffer
    while ((currentChar = fgetc(filePtr)) != EOF) {
        // Fill the buffer with only alphanumeric characters
        if (isalnum(currentChar) && buffIndex < 1023) {
            buffer[buffIndex] = tolower(currentChar);
            buffIndex++;
        }
        // If we hit a separator(space or punctuation), close the buffer
        else {
            buffer[buffIndex] = 0;
            if (buffIndex) {
                // If the buffer is a palindrome, print it
                if (palindromeSensor(buffer))
                    printf(RED_TEXT "%s is a palindrome" RESET "\n", buffer);
            }
            buffIndex = 0;
        }
    }
    // Handle the edge case when the file doesn't end with a separator and the buffer is not empty
    if (buffIndex) {
        buffer[buffIndex] = 0;
        if (palindromeSensor(buffer))
            printf(RED_TEXT "%s is a palindrome" RESET "\n", buffer);
    }
    // Close the file
    fclose(filePtr);
}


/*
 * deleteNonAlph - Deletes all non alphanumeric and non space characters from the given file
 * @fileName: the name of the file
 * Return: (void)
 */
void deleteNonAlph(char fileName[]) {
    // Open the file in read mode
    FILE *filePtr = fopen(fileName, "r");
    if (!filePtr) {
        perror("Fatal: Can't open File: ");
        exit(1);
    }

    // Open a temporary file to replace the original after the modifications
    FILE *newfile = fopen("tmp.txt", "w");
    if (!newfile) {
        perror("Fatal: Can't open File: ");
        exit(1);
    }

    int currentChar = 0;
    // Iterate through the file character by character and filter non-alphanumeric and non-space characters
    while ((currentChar = fgetc(filePtr)) != EOF) {
        if (isalnum(currentChar) || isspace(currentChar))
            fputc(currentChar, newfile);
    }
    // Close both files, delete the original, then replace it by the temporary file
    fclose(filePtr);
    fclose(newfile);
    remove(fileName);
    rename("tmp.txt", fileName);
}


/*
 * countGivenChar - Counts the number of occurrences of the target character in the given file
 * @fileName: the name of the file to check
 * @target: the target character to count
 * Return: (void)
 */
void countGivenChar(char fileName[], char target) {
    // Open the file in read mode
    FILE *filePtr = fopen(fileName, "r");
    if (!filePtr) {
        perror("Fatal: Can't open File: ");
        exit(1);
    }

    int currentChar = 0;
    int occurrenceCount = 0;
    
    // Convert the target to lowercase to simplify the check
    char lowerTarget = tolower(target);
    
    // Iterate through the file character by character
    while ((currentChar = fgetc(filePtr)) != EOF) {
        // Convert the current character to lowercase to simplify the check, and count each time we find a match
        if (tolower(currentChar) == lowerTarget)
            occurrenceCount++;
    }
    // Close the file, and print the number of occurrences
    fclose(filePtr);
    printf(MAGENTA_BG "The number of occurrences of the character '%c' is %d" RESET "\n", target, occurrenceCount);
}
