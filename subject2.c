#include "files.h"

/*
 * compareFiles - Checks if the two given files are identical or different
 * @fileName1: the first file's name
 * @fileName2: the second file's name
 * Return: 1 if both files are identical, else 0
 */
int compareFiles(char fileName1[], char fileName2[]) {
    // Open the first file in read mode
    FILE *file1ptr = fopen(fileName1, "r");
    if (!file1ptr) {
        perror("Fatal: Couldn't Open File: ");
        exit(1);
    }
    
    // Open the second file in read mode
    FILE *file2ptr = fopen(fileName2, "r");
    if (!file2ptr) {
        perror("Fatal: Couldn't Open File: ");
        exit(1);
    }

    // Calculate the size of the first file using fseek() and ftell()
    fseek(file1ptr, 0, SEEK_END);
    long filesize1 = ftell(file1ptr);
    rewind(file1ptr);

    // Calculate the size of the second file using fseek() and ftell()
    fseek(file2ptr, 0, SEEK_END);
    long filesize2 = ftell(file2ptr);
    rewind(file2ptr);

    // If the sizes are different, they can't be the same
    if (filesize1 != filesize2) {
        fclose(file1ptr);
        fclose(file2ptr);
        return 0;
    }

    // if the sizes are equal, we check if the equality is consistent at the character level, and return 0 if we find a difference
    int currentChar1 = 0, currentChar2 = 0;
    while ((currentChar1 = fgetc(file1ptr)) != EOF && (currentChar2 = fgetc(file2ptr)) != EOF) {
        if (currentChar1 != currentChar2) {
            fclose(file1ptr);
            fclose(file2ptr);
            return 0;
        }
    }
    
    // If we get to this point the files must be identical, we close the files and return 1 to signal it
    fclose(file1ptr);
    fclose(file2ptr);
    return 1;
}

/*
 * concatenateFiles - Concatenates the two given files and writes the result in "result.txt"
 * @fileName1: the first file's name
 * @fileName2: the second file's name
 * Return: (void)
 */
void concatenateFiles(char fileName1[], char fileName2[]) {
    // Open the first file in read mode
    FILE *file1ptr = fopen(fileName1, "r");
    if (!file1ptr) {
        perror("Fatal: Couldn't Open File: ");
        exit(1);
    }

    // Open the second file in read mode
    FILE *file2ptr = fopen(fileName2, "r");
    if (!file2ptr) {
        perror("Fatal: Couldn't Open File: ");
        exit(1);
    }

    // Create a new file where to put the result, and open it in write mode
    FILE *newfile = fopen("result.txt", "w");
    if (!newfile) {
        perror("Fatal: Couldn't Open File: ");
        exit(1);
    }

    // Get the filesize of the first file using fseek() and ftell(), use it to allocate a buffer with filesize1 + 1 as its size
    fseek(file1ptr, 0, SEEK_END);
    long filesize1 = ftell(file1ptr);
    rewind(file1ptr);
    char* buffer1 = malloc(sizeof(char) * filesize1 + 1);

    // Get the filesize of the second file using fseek() and ftell(), use it to allocate a buffer with filesize2 + 1 as its size
    fseek(file2ptr, 0, SEEK_END);
    long filesize2 = ftell(file2ptr);
    rewind(file2ptr);
    char *buffer2 = malloc(sizeof(char) * filesize2 + 1);
    
    // Read the first and second file in the first buffer and second buffer respectively at once using fread()
    fread(buffer1, sizeof(char), filesize1, file1ptr);
    fread(buffer2, sizeof(char), filesize2, file2ptr);

    // Write the first buffer in the result file at once, check if it ends with a newline, if not, add it, then write the second buffer at once using fwrite()
    fwrite(buffer1, sizeof(char), filesize1, newfile);
    if (filesize1 > 1 && buffer1[filesize1 - 1] != '\n')
        fputc('\n', newfile);
    fwrite(buffer2, sizeof(char), filesize2, newfile);

    // Free the allocated buffers then close the files
    free(buffer1);
    free(buffer2);
    fclose(file1ptr);
    fclose(file2ptr);
    fclose(newfile);
}


/*
 * replaceGivenWord - Replaces the target string with the replacement string in the given file
 * @fileName: the name of the file
 * @target: the target string to replace
 * @replacement: the replacement string for the target
 * Return: (void)
 */
void replaceGivenWord(char fileName[], char target[], char replacement[]) {
    // Open the file in read mode
    FILE *filePtr = fopen(fileName, "r");
    if (!filePtr) {
        perror("Fatal: Couldn't Open File: ");
        exit(1);
    }
    
    // Open a temporary file which is going to replace the original after all the modifications 
    FILE *newfile = fopen("tmp.txt", "w");
    if (!newfile) {
        perror("Fatal: Couldn't Open File: ");
        exit(1);
    }

    char buffer[1024];
    int buffIndex = 0, currentChar = 0;
    
    lowerBuffer(target);
    // Iterate through the file character by character
    while ((currentChar = fgetc(filePtr)) != EOF) {
        // If the current character is not a separator(space/newline or punctuation), add it to the buffer
        if (isalnum(currentChar) && buffIndex < 1023) {
            buffer[buffIndex] = currentChar;
            buffIndex++;
        }
        // If the current character is a separator, close the buffer
        else {
            buffer[buffIndex] = 0;
            
            if (buffIndex) {
                // Convert the buffer to lowercase for case insensitive comparison
                lowerBuffer(buffer);
                // If the buffer doesn't match the target, write it as is
                if (strcmp(buffer, target) != 0)
                    fputs(buffer, newfile);

                // If the buffer matches the target, write the replacement string instead
                else
                    fputs(replacement, newfile);

                // Crucial! Write the separator afterwards or the resulting file won't contain spaces and punctuation
                fputc(currentChar, newfile);
                // Reset the buffer index to start reading the next word
                buffIndex = 0;
            }
        }
    }
    // Handle the edge case where the file doesn't end with a separator
    if (buffIndex) {
        buffer[buffIndex] = 0;
        lowerBuffer(buffer);
        if (strcmp(buffer, target))
            fputs(buffer, newfile);
        else
            fputs(replacement, newfile);
    }
    // Close both files, delete the original, and replace it with the temporary file
    fclose(filePtr);
    fclose(newfile);
    remove(fileName);
    rename("tmp.txt", fileName);
}
