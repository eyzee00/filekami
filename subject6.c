#include "files.h"

/*
 * isForbidden - Checks if the given buffer is in the forbiddenList
 * @forbiddenList: an array of strings containing forbidden words
 * @buffer: the buffer to check against the list
 * @filterCount: the number of forbidden words in the list
 * Return: 1 if it is forbidden, 0 if it's not
 */
int isForbidden(char forbiddenList[MAXFILTER][MAXLENGTH], int filterCount, char buffer[]) {
    // Iterate through the forbiddenList until we find a match or until we reach the end
    for (int i = 0; i < filterCount; i++)
        // If we find a match, then the given buffer is forbidden
        if (!strcmp(buffer, forbiddenList[i]))
            return 1;

    // If we iterate through the whole list and don't find a match, then it's not a forbidden word
    return 0;
}


/*
 * lowerBuffer - Converts all the characters in the buffer to lowercase
 * @buffer: the buffer to operate on
 * Return: (void)
 */
void lowerBuffer(char buffer[]) {
    // If the buffer is empty, just return
    if (!buffer || !(*buffer))
        return;

    // Iterate through the buffer character by character, and convert it to lowercase
    for (int i = 0; buffer[i]; i++)
        buffer[i] = tolower(buffer[i]);
}


/*
 * theGreatFilter - Takes a target file and filter file, and removes all occurences appearing in the filter file from the target
 * @targetFile: the file to sanitize
 * @filterFile: the filter file used to sanitize the target
 * Return: (void)
 */
void theGreatFilter(char targetFile[], char filterFile[]) {
    // Open the target file in read mode
    FILE *targetPtr = fopen(targetFile, "r");
    if (!targetPtr) {
        perror("Fatal: Can't Open File");
        exit(1);
    }

    //Open the filter file in read mode
    FILE *filterPtr = fopen(filterFile, "r");
    if (!filterPtr) {
        perror("Fatal: Can't Open File");
        exit(1);
    }

    // Open atemporary file in write mode where we'll store the resulting modifications
    FILE *newFile = fopen("tmp.txt", "w");
    if (!newFile) {
        perror("Fatal: Can't Open File");
        exit(1);
    }
    

    char filterArray[MAXFILTER][MAXLENGTH];
    int filterCount = 0;

    // Create a filter list, fill it by all the tokens appearing in the filter file, and make sure to not surpass the maximum length of the list
    // This way we avoid reading though the whole file each time, but through the list instead
    while (filterCount < MAXFILTER && fscanf(filterPtr, "%1023s", filterArray[filterCount]) != -1) {
        // Convert all the words into lowercase to reduce complexity
        lowerBuffer(filterArray[filterCount]);
        filterCount++;
    }
    char currentTarget[MAXLENGTH], placeholder[MAXLENGTH];
    int currentChar = 0, targetIndex = 0;
    
    // Iterate through the file character by character
    while ((currentChar = fgetc(targetPtr)) != EOF) {
        // If the character is alphanumeric, put it in the buffer
        if (isalnum(currentChar) && targetIndex < MAXLENGTH - 1) {
            currentTarget[targetIndex] = currentChar;
            targetIndex++;
        }
        // if we hit a separator(space, punctuation), close the buffer
        else {
            currentTarget[targetIndex] = 0;
            // If the buffer is not empty, copy the buffer into a placeholder and convert the copy to lowercase
            if (targetIndex) {
                strcpy(placeholder, currentTarget);
                lowerBuffer(placeholder);
                // Write the buffer in the temporary file if it's not forbidden
                if (!isForbidden(filterArray, filterCount, placeholder))
                    fputs(currentTarget, newFile);
            }
            // Put separators in the temporary file regardless and reset the buffer index for the next word
            fputc(currentChar, newFile);
            targetIndex = 0;
        }
    }

    // Handle the edge case where the file doesn't end with a separator
    if (targetIndex) {
        currentTarget[targetIndex] = 0;
        strcpy(placeholder, currentTarget);
        lowerBuffer(placeholder);
        if (!isForbidden(filterArray, filterCount, placeholder))
            fputs(currentTarget, newFile);
    }

    // Close all the files, remove the original, and replace it with the temporary file
    fclose(targetPtr);
    fclose(filterPtr);
    fclose(newFile);
    remove(targetFile);
    rename("tmp.txt", targetFile);
} 


/*
 * deleteEmptyLines - Deletes empty lines, empty lines are lines which contain only spaces or no characters at all
 * @fileName: the file to sanitize
 * Return: (void)
 */
void deleteEmptyLines(char fileName[]) {
    // Open the file in read mode
    FILE *filePtr = fopen(fileName, "r");
    if (!filePtr) {
        perror("Fatal: Can't Open File: ");
        exit(1);
    }

    // Open a replacement file which is going to replace the original after the modifications
    FILE *newFile = fopen("tmp.txt", "w");
    if (!newFile) {
        perror("Fatal: Can't Open File: ");
        exit(1);
    }

    char line[MAXLENGTH];
    int isEmpty = 0;
    
    // Read from the file line by line, fgets() stops at a newline, or if it reached MAXLENGTH
    while (fgets(line, MAXLENGTH, filePtr) != NULL) {
        // Set the isEmpty flag to 1, if we the line has any characters aside from spaces, we set it to 0
        isEmpty = 1;
        for (int i = 0; line[i]; i++) {
            if (!isspace(line[i])) {
                isEmpty = 0;
                break;
            }
        }
        // If the line is not empty, we write it in the replacement file
        if (!isEmpty)
            fputs(line, newFile);
    }

    // Close both file, remove the original, and replace it with the replacement
    fclose(filePtr);
    fclose(newFile);
    remove(fileName);
    rename("tmp.txt", fileName);
}

/*
 * swap - Swaps two pointers to char by swapping the addresses they're pointing to
 * @string1: the address of the first pointer to char
 * @string2: the address of the second pointer to char
 * Return: (void)
 */
void swap(char **string1, char **string2) {
    char *temp = *string1;
    *string1 = *string2;
    *string2 = temp;
}

/*
 * partitioner - makes sure the pivot(we choose the pivot to be the last element) is in a sorted position
 * (all elements smaller than the pivot are put to its left, and all elements bigger than the pivot are put to its right)
 *
 * @lineArray: the array of strings we are attempting to sort
 * @lowIndex: the index of the first element
 * @highIndex: the index of the last element
 * Return: the index of the pivot after it's sorted
 */
int partitioner(char **lineArray, int lowIndex, int highIndex) {
    // Set pivot to point to the last element(line)
    char *pivot = lineArray[highIndex];
    int wall, scout;
    
    // Use a scout to iterate through the list
    // Use wall as the separator between lines smaller than the pivot and lines bigger than the pivot
    for (scout = lowIndex, wall = lowIndex - 1; scout < highIndex; scout++) {
        // If the current line is smaller than the pivot, move the wall by a step, and swap it with the current line to account for it
        if (strcmp(lineArray[scout], pivot) < 0) {
            wall++;
            swap(&lineArray[wall], &lineArray[scout]);
        }
        // Else, do nothing
    }
    // After finding the correct position for the wall, swap it with the pivot, now the pivot is the wall
    // All the elements smaller than it are to its left, and elements bigger than it are to its right
    wall++;
    swap(&lineArray[wall], &lineArray[highIndex]);
    // Return the sorted position of the pivot
    return wall;
}


/*
 * quickSortLines - Sorts an array of strings recursively using the partitioner, a divide and conquer algorithm:
 * the partitioner naturaly divides the array into a subarray containing strings smaller than the pivot and a subarray containing
 * strings bigger than the pivot, we call the function recursively on both subarrays, until we have subarrays containing
 * only the sorted pivot, then the recursive calls stop and start resolving... we end up with a sorted array by the end
 *
 * @lineArray: the array of strings to sort
 * @lowIndex: the index of the first element
 * @highIndex: the index of the last element
 * Return: (void)
 * */
void quickSortLines(char **lineArray, int lowIndex, int highIndex) {
    // Only call recursively if the array(or subarray) contains more than one element
    if (lowIndex < highIndex) {
        // Partition the array into elements smaller than the pivot and elements bigger than the pivot(with the pivot in between)
        int pivotIndex = partitioner(lineArray, lowIndex, highIndex);
        
        // Call the function recursively to sort the elements smaller than the pivot using the same method (pivot excluded)
        quickSortLines(lineArray, lowIndex, pivotIndex - 1);
        // Call the function recursively to sort the elements bigger than the pivot using the same method (pivot excluded)
        quickSortLines(lineArray, pivotIndex + 1, highIndex);
    }
}

/*
 * sortLinesAlpha - Sorts the lines of the given file alphabetically using the quick sort algorithm
 * @fileName: the name of the file to sort
 * Return: (void)
 */
void sortLinesAlpha(char fileName[]) {
    // Open the file in read mode
    FILE *filePtr = fopen(fileName, "r");
    if (!filePtr) {
        perror("Fatal: Can't Open File: ");
        exit(1);
    }

    // Open a replacement file where we'll store the results
    FILE *newFile = fopen("tmp.txt", "w");
    if (!newFile) {
        perror("Fatal: Can't Open File: ");
        exit(1);
    }

    int capacity = MAXLINES;
    // Allocate an array of strings of size MAXLINES(200 lines max)
    char **lineArray = malloc(capacity * sizeof(char *));
    if (!lineArray) {
        perror("Fatal: Can't Allocate Memory: ");
        exit(1);
    }
    
    ssize_t charsRead = 0, lineCount = 0;
    size_t charsCount = 0;
    char *line = NULL;
    
    // Use getline() to read the file line by line, naturally getline() returns the number of characters read
    // If it fails or reaches the end of file, it returns -1
    while ((charsRead = getline(&line, &charsCount, filePtr)) != -1) {
        // If the lineCount surpasses the limit supported by the previously allocated array,
        // use realloc() to double the capacity of the array to support the remaining lines 
        if (lineCount >= capacity) {
            capacity = capacity * 2;
            lineArray = realloc(lineArray, capacity * sizeof(char *));
        }
        // Use readc(the count of character read by getline()) to allocate enough space for the line
        // then copy it to the corresponding row in lineArray
        lineArray[lineCount] = malloc(charsRead * sizeof(char) + 1);
        strcpy(lineArray[lineCount], line);
        // Increment lineCount to move to the next row in lineArray
        lineCount++;
    }
    free(line);
    // Only sort the array if it contains more than one line
    if (lineCount > 1) 
        quickSortLines(lineArray, 0, lineCount - 1);

    // Write the sorted lines in the replacement file, and free memory after writing each line
    for (int i = 0; i < lineCount; i++) {
        fputs(lineArray[i], newFile);
        free(lineArray[i]);
    }
    // Free the line list
    free(lineArray);


    // Close both files, remove the original, and replace it with the replacement file
    fclose(filePtr);
    fclose(newFile);
    remove(fileName);
    rename("tmp.txt", fileName);
}
