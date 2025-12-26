#include "files.h"

/*
 * checkIfUnique - Checks if the given buffer doesn't exist in the given file
 * @filePtr: pointer to FILE, the list of unique tokens
 * @buffer: the token to check the existence of
 * Return: 1 if it doesn't exist, else 0
 */
int checkIfUnique(FILE *filePtr, char buffer[]) {
    // Crucial! rewind the pointer to the start to avoid conflicts with the calling function
    rewind(filePtr);

    char currentWord[1024];
    int unique = 0;

    // Iterate through the list word by word
    while(fscanf(filePtr, "%1023s", currentWord) == 1) {
        // If the word length of both the current word and the buffer is different, then they can't be identical, jump to the next word
        if (strlen(currentWord) != strlen(buffer))
            continue;
        // If the sizes are equal, Set the unique flag to 0 and use it as a signal
        unique = 0;
        for (int i = 0; i < (int)strlen(currentWord); i++) {
            // If there is a mismatch, the buffer is different from the current word, no need to loop further
            if (currentWord[i] != buffer[i]) {
                unique = 1;
                break;
            }
        }
        // If the unique flag is 0, then the buffer must match the current word, therefore the buffer is not unique, no need to loop further
        if (unique == 0)
            return 0;
    }
    // If we iterate through the whole list and find no matches, the buffer must be unique
    return 1;
}


/*
 * countLinesAndUniqueOccu - Counts the number of lines and the number of unique occurrences in the given file
 * @fileName: the name of the file to operate on
 * Return: (void)
 */
void countLinesAndUniqueOccu(char fileName[]) {
    // Open the file in read mode
    FILE *filePtr = fopen(fileName, "r");
    if (!filePtr) {
        perror("Fatal: Couldn't open File: ");
        exit(1);
    }

    // Open atemporary file where to store the unique tokens
    FILE *uniqueList = fopen("unique.txt", "w+");
    if (!uniqueList) {
        perror("Fatal: Couldn't open File: ");
        exit(1);
    }

    char buffer[1024];
    int currentChar = 0, buffIndex = 0, lineCount = 0, numberOfUniqueOccu = 0;

    // Iterate through each character in the file
    while ((currentChar = fgetc(filePtr)) != EOF) {
        // If we encounter a newline, count it
        if (currentChar == '\n')
            lineCount++;
        // If we encounter a character that is not a seperator(punctuations, space), write it in the buffer
        if (isalnum(currentChar) && buffIndex < 1023) {
            buffer[buffIndex] = tolower(currentChar);
            buffIndex++;
        }

        // If we encounter a separator, close the buffer, and start the checks
        else {
            buffer[buffIndex] = 0;
            // If the buffer is not empty, and is a unique token, write in the token list, and count it as a unique occurrence
            if (buffIndex > 0 && checkIfUnique(uniqueList, buffer)) {
                fputs(buffer, uniqueList);
                fputc('\n', uniqueList);
                numberOfUniqueOccu++;
            }
            buffIndex = 0;
        }
    }
    // Handle the edge case where the file doesn't end with a separator
    if (buffIndex) {
        buffer[buffIndex] = 0;
        if (checkIfUnique(uniqueList, buffer))
            numberOfUniqueOccu++;
    }
    // Print the number of lines and unique occurrences, then close both files, and remove the unique tokens file
    printf(MAGENTA_BG "The number of lines is %d | The number of unique occurrences is %d" RESET "\n", lineCount, numberOfUniqueOccu);
    fclose(filePtr);
    fclose(uniqueList);
    remove("unique.txt");
}

/*
 * inverseWords - Inverses words inside the given file
 * @fileName: the name of the file to modify
 * Return: (void)
 */
void inverseWords(char fileName[]) {
    // Open the file in read mode
    FILE *filePtr = fopen(fileName, "r");
    if (!filePtr) {
        perror("Fatal: Couldn't open File: ");
        exit(1);
    }
    
    // Open a temporary file where to store the modifications and remove the original afterwards
    FILE *newfile = fopen("tmp.txt", "w");
    if (!newfile) {
        perror("Fatal: Couldn't open File: ");
        exit(1);
    }

    char buffer[1024];
    int buffIndex = 0, currentChar = 0;

    // Iterate through the file character by character
    while ((currentChar = fgetc(filePtr)) != EOF) {
        // If the character is alphanumeric, write in the buffer
        if (isalnum(currentChar) && buffIndex < 1023) {
            buffer[buffIndex] = currentChar;
            buffIndex++;
        }

        // If we hit a separator, close the buffer and start the checks
        else {
            buffer[buffIndex] = 0;
            // If the buffer is not empty, write it in the temporary file in reverse
            if (buffIndex) {
                buffIndex--;
                while (buffIndex >= 0) {
                    fputc(buffer[buffIndex], newfile);
                    buffIndex--;
                }
            }
            // Then write the separator to conserve the file structure
            fputc(currentChar, newfile);
            buffIndex = 0;
        }
    }

    // Handle the edge case where a file doesn't end with a separator
    if (buffIndex) {
        buffIndex--;
        while (buffIndex >= 0) {
            fputc(buffer[buffIndex], newfile);
            buffIndex--;
        }
    }
    // Close both files, delete the original, and replace it with the temporary file
    fclose(filePtr);
    fclose(newfile);
    remove(fileName);
    rename("tmp.txt", fileName);
}
/*
 * occurencesOverN - Counts all the tokens that appear more than n times in the given file
 * @fileName: the name of the file to operate on
 * @n: the limit to check all tokens against
 * Return: (void)
 */

void occurencesOverN(char fileName[], int n) {
    // Open the file in read mode
    FILE *filePtr = fopen(fileName, "r");
    if (!filePtr) {
        perror("Fatal: Couldn't open File: ");
        exit(1);
    }

    // Open a temporary file where to store all the unique tokens in read/write mode
    FILE *uniqueList = fopen("unique.txt", "w+");
    if (!uniqueList) {
        perror("Fatal: Couldn't open File: ");
        exit(1);
    }

    // Open a temporary file where to store all the tokens in read/write mode
    FILE *tokenList = fopen("tokens.txt", "w+");
    if (!tokenList) {
        perror("Fatal: Couldn't open File: ");
        exit(1);
    }
    
    char buffer[1024];
    int buffIndex = 0, currentChar = 0;

    // Iterate through the file character by character and fill the buffer
    while ((currentChar = fgetc(filePtr)) != EOF) {
        // If the current character is alphanumeric, write it in the buffer
        if (isalnum(currentChar) && buffIndex < 1023) {
            buffer[buffIndex] = currentChar;
            buffIndex++;
        }
        
        // If we hit a separator(space/punctuations), close the buffer
        else {
            buffer[buffIndex] = 0;
            // If the buffer is not empty, check it against the unique tokens already stored
            if (buffIndex) {
                // If it's unique, put it in the unique file
                if (checkIfUnique(uniqueList, buffer)) {
                    fputs(buffer, uniqueList);
                    fputc('\n', uniqueList);
                }
                // Put it in the token file regardless of its uniqueness
                fputs(buffer, tokenList);
                fputc('\n', tokenList);
            }
            // Reset the buffer index to store the following token
            buffIndex = 0;
        }
    }

    // Handle the edge case where the file doesn't end with a separator
    if (buffIndex) {
        buffer[buffIndex] = 0;
        if (checkIfUnique(uniqueList, buffer))
            fputs(buffer, uniqueList); 
        fputs(buffer, tokenList);
    }
    
    // Crucial! Rewind the pointer to the start of the unique file
    rewind(uniqueList);
    
    char currentWord[1024], currentToken[1024];
    int occurrenceCounter = 0;
    // Iterate through the unique file token by token
    while (fscanf(uniqueList, "%1023s", currentWord) == 1) {
        // Crucial! Rewind the pointer to the start of the token file, in each iteration
        rewind(tokenList);
        // Iterate through the token list token by token
        while (fscanf(tokenList, "%1023s", currentToken) == 1) {
            // If we find a match, we count it
            if (!strcmp(currentToken, currentWord))
                occurrenceCounter++;
        }
        // If the current unique token appeared more than n times in the token list, print it
        if (occurrenceCounter > n)
            printf(RED_TEXT "The word: '%s' occurred %d times" RESET "\n", currentWord, occurrenceCounter);
        // Reset the counter for the following unique token
        occurrenceCounter = 0;
    }
    // Close all the files, and delete the helper/temporary files
    fclose(filePtr);
    fclose(uniqueList);
    fclose(tokenList);
    remove("tokens.txt");
    remove("unique.txt");
}
