#include "files.h"

/*
 * shortestAndLongestWord - Finds the longest and shortest word, then prints them + their respective length
 * @fileName: name of the file to operate on
 * Return: (void)
 */

void shortestAndLongestWord(char fileName[]) {
    // Open the file in read mode
    FILE *filePtr = fopen(fileName, "r");
    if (!filePtr) {
        perror("Fatal: Can't Open the File: ");
        exit(1);
    }
    
    char readBuff[1024], maxToken[1024], minToken[1024];
    int currentChar = 0, buffIndex = 0, maxLength = 0, minLength = 0, isFirstToken = 1;
   
    // Iterate through the file character by character
    while ((currentChar = fgetc(filePtr)) != EOF) {
        // If the character is alphanumeric, put it in the buffer
        if (isalnum(currentChar) && buffIndex < 1023) {
            readBuff[buffIndex] = currentChar;
            buffIndex++;
        }
        // If the character is a separator(space/punctuation), close the buffer
        else {
            if (buffIndex) {
                readBuff[buffIndex] = 0;
                // If the current token is shorter than the short token, replace the short token with it
                // If it's the first token, enter regardless
                if (isFirstToken || buffIndex < minLength) {
                    strcpy(minToken, readBuff);
                    minLength = buffIndex;
                }
                // If the current token is longer than the long token, replace the long token with it
                // If it's the first token, enter regardless
                if (isFirstToken || buffIndex > maxLength) {
                    strcpy(maxToken, readBuff);
                    maxLength = buffIndex;
                }
                isFirstToken = 0;
                buffIndex = 0;
            }
        }
    }
    // Handle the edge case where the file doesn't end with a separator
    
    if (buffIndex) {
        readBuff[buffIndex] = 0;
        // If the current token is shorter than the short token, replace the short token with it
        // If it's the first token, enter regardless
        if (isFirstToken || buffIndex < minLength) {
            strcpy(minToken, readBuff);
            minLength = buffIndex;
        }
        // If the current token is longer than the long token, replace the long token with it
        // If it's the first token, enter regardless
        if (isFirstToken || buffIndex > maxLength) {
            strcpy(maxToken, readBuff);
            maxLength = buffIndex;
        }
        // This might be the first word we read, example "(space) hello"
        // no separator at the end, a leading space so the flag won't be set to 0
        isFirstToken = 0;
    }
    
    // If the flag is still 1, the long and short token must be empty, and no tokens could be extracted from the file
    if (isFirstToken) {
        puts(MAGENTA_BG "This file contains no alphanumeric words, try again with a valid file" RESET);
    }
    // If the flag is set to 0, then we must have tokens to print
    else
        printf(MAGENTA_BG "'%s' of length %d is the longest word | '%s' of length %d is the shortest word" RESET "\n", maxToken, maxLength, minToken, minLength);
    fclose(filePtr);
}


/*
 * getAverageWordLength - Calculate the average length of the words in the given file
 * @filename: the name of the file to operate on
 * Return: (void)
 */
void getAverageWordLength(char fileName[]) {
    // Open the file in read mode
    FILE *filePtr = fopen(fileName, "r");
    if (!filePtr) {
        perror("Fatal: Can't Open File: ");
        exit(1);
    }

    int currentChar = 0, totalLength = 0, numberOfTokens = 0, isInsideToken = 0;
    
    // Iterate through the file character by character
    while ((currentChar = fgetc(filePtr)) != EOF) {
        // If the character is alphanumeric, increment the total length, and signal that we are inside a token
        if (isalnum(currentChar)) {
            isInsideToken = 1;
            totalLength++;
        }
        // If we hit a separator, the token is complete, we increment the number of tokens, and reset the flag to signal moving on to the next word
        else {
            if (isInsideToken) {
                numberOfTokens++;
            }
            isInsideToken = 0;
        }
    }
    // Handle the edge case where the file doesn't end with a separator and we're still inside a token
    if (isInsideToken) {
        numberOfTokens++;
    }
    // If the file is not empty, then we can calculate the average
    if (numberOfTokens) {
        printf(RED_TEXT "The sum of the length of all the words: %d | The total number of words: %d" RESET "\n", totalLength, numberOfTokens);
        printf(MAGENTA_BG "Therefore, the average length of the words in the given file %.4f" RESET "\n", totalLength / (float)numberOfTokens);
    }
    // Close the file
    fclose(filePtr);
}


/*
 * shortestAndLongestLine - Finds the longest and shortest line and prints them along with their length
 * @fileName: name of the file to operate on
 * Return: (void)
 */
void shortestAndLongestLine(char fileName[]) {
    // Open the file in read mode
    FILE *filePtr = fopen(fileName, "r");
    if (!filePtr) {
        perror("Fatal: Can't Open File: ");
        exit(1);
    }

    size_t lineLen = 0;
    ssize_t charsRead = 0, maxLength = 0, minLength = 0;
    int isFirstLine = 1;
    char *currentLine = NULL, *shortestLine = NULL, *longestLine = NULL;
    
    // Use getline to read a full line, getline handles the memory allocation and returns the number of characters read
    // If getline reaches the end of the stream or fails, it returns -1
    while ((charsRead = getline(&currentLine, &lineLen, filePtr)) != -1) {
        // getline reads up to a newline or end of file
        // If we find a newline at the end of the read line, we trim it to simplify comparisons
        if (charsRead && currentLine[charsRead - 1] == '\n') {
            currentLine[charsRead - 1] = 0;
            charsRead--;
        }
        // If the current line is smaller than the short line, we free the short line, and replace it with a duplicate of the currentLine
        // If this is the first line we read, we enter regardless
        if (isFirstLine || charsRead < minLength) {
            free(shortestLine);
            shortestLine = strdup(currentLine);
            minLength = charsRead;
        }
        // If the current line is longer than the long line, we free the long line, and replace it with a duplicate of the currentLine
        // If this is the first line we read, we enter regardless
        if (isFirstLine || charsRead > maxLength) {
            free(longestLine);
            longestLine = strdup(currentLine);
            maxLength = charsRead;
        }
        // Once we read once, we set the flag to 0 to signal it
        isFirstLine = 0;
    }
    // Free the memory allocated by getline
    free(currentLine);
    
    // Only print the result if we have a result to print
    if (longestLine && shortestLine) {
        printf(MAGENTA_BG "Longest line of length %ld: %s\n", maxLength, longestLine);
        printf("Shortest line of length %ld: %s" RESET "\n", minLength, shortestLine);
    }
    // Free the memory allocated by strdup, which handles memory allocation automatically like getline
    free(shortestLine);
    free(longestLine);
    // CLose the file
    fclose(filePtr);
}
