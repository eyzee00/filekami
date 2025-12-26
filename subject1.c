#include "files.h"

/*
 * deleteGivenChar - eliminates the target character from the given File
 * @fileName: The name of the file to clean
 * @target: the character to eliminate
 * Return: (void)
 */

void deleteGivenChar(char fileName[], char target) {
    // Open the file in read mode
    FILE *filePtr = fopen(fileName, "r");
    if (!filePtr) {
        perror("Fatal: Couldn't open File ");
        exit(1);
    }
    // Open a temporary file in write mode to replace the old one with added modifications
    FILE *newFile = fopen("tmp.txt", "w");
    if (!newFile) {
        perror("Fatal: Couldn't open File: ");
        exit(1);
    }
    
    // Iterate through the file and write all the characters except the target
    int currentChar = 0;
    while((currentChar = fgetc(filePtr)) != EOF) {
        if (tolower(currentChar) != target) {
            fputc(currentChar, newFile);
        }
    }
    // Close the opened files, delete the old file, and replace it with the new one
    fclose(filePtr);
    fclose(newFile);
    remove(fileName);
    rename("tmp.txt", fileName);
}


/*
 * lowerToUpper - converts all the alphabetic characters to uppercase
 * @fileName: Name of the file to operate on
 * Return: (void)
 * */
void lowerToUpper(char fileName[]) {
    // Open the file in read mode
    FILE *filePtr = fopen(fileName, "r");
    if (!filePtr) {
        perror("Fatal: Couldn't open File: ");
        exit(1);
    }
    
    // Open a temporary which is going to replace the original after the modifications
    FILE *newFile = fopen("tmp.txt", "w");
    if (!newFile) {
        perror("Fata: Couldn't open File: ");
        exit(1);
    }
    
    // Iterate through the file, convert all alphabetic characters to uppercase, and write them into the temporary file
    int currentChar = 0;
    while ((currentChar = fgetc(filePtr)) != EOF) {
        if (currentChar >= 97 && currentChar <= 122)
            fputc(currentChar - 32, newFile);
        else
            fputc(currentChar, newFile);
    }
    // Close both files, delete the original, and replace it with the temporary file
    fclose(filePtr);
    fclose(newFile);
    remove(fileName);
    rename("tmp.txt", fileName);
}


/*
 * upperToLower - converts all the alphabetic characters to lowercase
 * @fileName: Name of the file to operate on
 * Return: (void)
 * */
void upperToLower(char fileName[]) {
    // Open the file in read mode
    FILE *filePtr = fopen(fileName, "r");
    if (!filePtr) {
        perror("Fatal: Couldn't open File: ");
        exit(1);
    }
    
    // Open a temporary file which is going to replace the original after the modifications
    FILE *newFile = fopen("tmp.txt", "w");
    if (!newFile) {
        perror("Fata: Couldn't open File: ");
        exit(1);
    }

    // Iterate through the file, convert all alphabetic characters to uppercase, then write them into the temporary file
    int currentChar = 0;
    while ((currentChar = fgetc(filePtr)) != EOF) {
        if (currentChar >= 65 && currentChar <= 90)
            fputc(currentChar + 32, newFile);
        else
            fputc(currentChar, newFile);
    }
    // Close both files, delete the original, and replace it with the temporary file
    fclose(filePtr);
    fclose(newFile);
    remove(fileName);
    rename("tmp.txt", fileName);
}

/*
 * countOccurence - Counts the occurrences of a given string in the given File
 * @fileName: the name of the file to operate on
 * @target: the string to count
 * Return: 0
 * */
int countOccurence(char fileName[], char target[]) {
    char buffer[1024];

    // Open the file in read mode
    FILE *filePtr = fopen(fileName, "r");
    if (!filePtr) {
        perror("Fatal: Couldn't open File: ");
        exit(1);
    }
    
    lowerBuffer(target);
    // Iterate through the file word by word, and count when it matches the target
    int occurenceCounter = 0;
    while (fscanf(filePtr, "%1023s", buffer) == 1) {
        lowerBuffer(buffer);
        if (!strcmp(target, buffer))
            occurenceCounter++;
    }
    
    // Close the file
    fclose(filePtr);
    return occurenceCounter;
}
