#include <files.h>

void subjectOneHandler() {
    char fileName[50], target = 0;
    int choice = 0;
    
    putchar('\n');
    printf(MAGENTA_BG "Welcome to subject 1, select one of the following options: " RESET);
    while(1) {
        puts("\n--------------------------------------------------------------------------------------------------------------------------------------\n");
        puts(ORANGE_TEXT "----> Select 1 to delete a given character from a text file of choice");
        puts("----> Select 2 to convert the given file's text to uppercase");
        puts("----> Select 3 to convert the given file's text to lowercase");
        puts("----> Select 4 to count the occurrences of a given word in the given file");
        puts("----> Select 0 to quit to the main menu");

        printf("\nYour choice is: " RESET);
        scanf("%d", &choice);
        if (choice >= 1 && choice <= 4) {
            puts("\n--------------------------------------------------------------------------------------------------------------------------------------\n");
            printf(ORANGE_TEXT "Enter the name of the file: " RESET);
            scanf("%s", fileName);

        }

        switch (choice) {
            case 1:
                printf(ORANGE_TEXT "Enter the target character to eliminate: " RESET);
                scanf(" %c", &target);
                deleteGivenChar(fileName, target);
                puts(MAGENTA_BG "Character eliminated succesfully!" RESET);
                break;

            case 2:
                lowerToUpper(fileName);
                puts(MAGENTA_BG "Converted the text to uppercase succesfully!" RESET);
                break;
                
            case 3:
                upperToLower(fileName);
                puts(MAGENTA_BG "Converted the text to lowercase succesfully!" RESET);
                break;

            case 4:
                printf(ORANGE_TEXT "Enter the target word to count: " RESET);
                char targetWord[50];
                scanf("%49s", targetWord);
                printf(MAGENTA_BG "The word you entered appeared %d times" RESET, countOccurence(fileName, targetWord));
                break;

            case 0:
                return;

            default:
                continue;
        }
        target = 0;
        choice = 0;
    }
}


void subjectTwoHandler(void) {
    char fileName1[50], fileName2[50], replacement[50], target[50];
    int choice = 0;
    
    putchar('\n');
    puts(MAGENTA_BG "Welcome to subject 2, select one of the following options to proceed:" RESET);
    while(1) {
        puts("\n--------------------------------------------------------------------------------------------------------------------------------------\n");
        puts(ORANGE_TEXT "----> Select 1 to compare two files");
        puts("----> Select 2 to concatenate two files and write the result in a third file named 'result.txt'");
        puts("----> Select 3 to replace a given word by a given replacement in a given file");
        puts("----> Select 0 to quit to the main menu!");

        printf("\nYour choice is: " RESET);
        scanf("%d", &choice);

        if (choice == 1 || choice == 2) {
            puts("\n--------------------------------------------------------------------------------------------------------------------------------------\n");
            printf(ORANGE_TEXT "Enter the first file's name: " RESET);
            scanf("%49s", fileName1);
            printf(ORANGE_TEXT "Enter the second file's name: " RESET);
            scanf("%49s", fileName2);
        }

        switch (choice) {
            case 1:
                if (compareFiles(fileName1, fileName2))
                    puts(MAGENTA_BG "The given files are identical!" RESET);
                else
                    puts(MAGENTA_BG "The given files are not identical" RESET);
                break;
            
            case 2:
                concatenateFiles(fileName1, fileName2);
                puts(MAGENTA_BG"The given files were concatenated in 'result.txt'" RESET);
                break;

            case 3:
                puts("\n--------------------------------------------------------------------------------------------------------------------------------------\n");
                printf(ORANGE_TEXT "Enter the name of the file: " RESET);
                scanf("%49s", fileName1);
                printf(ORANGE_TEXT "Enter the target word to replace: " RESET);
                scanf("%49s", target);
                printf(ORANGE_TEXT "Enter a replacement for the target: " RESET);
                scanf("%49s", replacement);
                replaceGivenWord(fileName1, target, replacement);
                puts(MAGENTA_BG"The given word have been replaced succesfully!" RESET);
                break;
            case 0:
                return;
            default:
                continue;
        }
    }
}

void subjectThreeHandler() {
    char fileName[50];
    int choice = 0, threshold = 0;

    putchar('\n');
    puts(MAGENTA_BG "Welcome to subject 3, select oe of the following options to proceed" RESET);
    while (1) {
        puts("\n--------------------------------------------------------------------------------------------------------------------------------------\n");
        puts(ORANGE_TEXT "----> Select 1 to count lines and the number of unique occurrences in a given file");
        puts("----> Select 2 to inverse words in the given file");
        puts("----> Select 3 to count the words occurring more than a given threshold in a given file");
        puts("----> Select 0 to return to the main menu");

        printf("\nYour choice is: " RESET);
        scanf("%d", &choice);

        if (choice >= 1 && choice <= 3) {
            puts("\n--------------------------------------------------------------------------------------------------------------------------------------\n");
            printf(ORANGE_TEXT "Enter the name of the file: " RESET);
            scanf("%49s", fileName);
        }
        switch (choice) {
            case 1:
                countLinesAndUniqueOccu(fileName);
                break;
            case 2:
                inverseWords(fileName);
                puts(MAGENTA_BG "Words have been inversed succesfully" RESET);
                break;
            case 3:
                printf(ORANGE_TEXT "Enter the threshold to consider: " RESET);
                scanf("%d", &threshold);
                occurencesOverN(fileName, threshold);
                break;
            case 0:
                return;
            default:
                continue;
        }
    }
}

void subjectFourHandler() {
    int choice = 0;
    char fileName[50], target = 0;

    putchar('\n');
    puts(MAGENTA_BG "Welcome to subject 4! Choose one of the following options to proceed" RESET);
    while(1) {
        puts("\n--------------------------------------------------------------------------------------------------------------------------------------\n");
        puts(ORANGE_TEXT "----> Select 1 to print all palindrome occurrences in the given file");
        puts("----> Select 2 to delete non alphanumeric characters and non space characters from the given file");
        puts("----> Select 3 to count the occurrences of a given character in the given file");
        puts("----> Select 0 to quit to the main menu!");

        printf("\nYour choice is: " RESET);
        scanf("%d", &choice);
        
        if (choice >= 1 && choice <= 3) {
            puts("\n--------------------------------------------------------------------------------------------------------------------------------------\n");
            printf(ORANGE_TEXT "Enter the name of the file: " RESET);
            scanf("%49s", fileName);
        }
        switch (choice) {
            case 1:
                detectPalindromes(fileName);
                break;
            case 2:
                deleteNonAlph(fileName);
                puts(MAGENTA_BG "Non Alphanumeric and non space characters were deleted succesfully" RESET);
                break;
            case 3:
                printf(ORANGE_TEXT "Enter the target character to count: " RESET);
                scanf(" %c", &target);
                countGivenChar(fileName, target);
                break;
            case 0:
                return;
            default:
                continue;
        }
    }
}

void subjectFiveHandler() {
    char fileName[50];
    int choice = 0;

    putchar('\n');
    puts(MAGENTA_BG "Welcome to subject 5! Choose one of the following options to proceed:" RESET);
    while (1) {
        puts("\n--------------------------------------------------------------------------------------------------------------------------------------\n");
        puts(ORANGE_TEXT "----> Select 1 to print the longest and shortest word with their respective length in the given file");
        puts("----> Select 2 to calculate the average length of the words in the given file");
        puts("----> Select 3 to print the shortest and longest line with their respective length");
        puts("----> Select 0 to quit to main menu");

        printf("\nYour choice is: " RESET);
        scanf("%d", &choice);
        if (choice >= 1 && choice <= 3) {
            puts("\n--------------------------------------------------------------------------------------------------------------------------------------\n");
            printf(ORANGE_TEXT "Enter the name of the file: " RESET);
            scanf("%49s", fileName);
        }

        switch (choice) {
            case 1:
                shortestAndLongestWord(fileName);
                break;
            case 2:
                getAverageWordLength(fileName);
                break;
            case 3:
                shortestAndLongestLine(fileName);
                break;
            case 0:
                return;
            default:
                continue;
        }
    }
}

void subjectSixHandler() {
    int choice = 0;
    char fileName[50], filterName[50];

    putchar('\n');
    puts(MAGENTA_BG "Welcome to subject 6! Choose one of the following options to proceed:" RESET);
    while (1) {
        puts("\n--------------------------------------------------------------------------------------------------------------------------------------\n");
        puts(ORANGE_TEXT "----> Select 1 to delete all occurrences in the given filter file present in the given target file");
        puts("----> Select 2 to delete all empty lines in the given file");
        puts("----> Select 3 to sort the lines of the given file alphabetically in ascending order");
        puts("----> Select 0 to return to main menu");

        printf("\nYour choice is: " RESET);
        scanf("%d", &choice);

        if (choice == 2 || choice == 3) {
            puts("\n--------------------------------------------------------------------------------------------------------------------------------------\n");
            printf(ORANGE_TEXT "Enter the name of the file: " RESET);
            scanf("%49s", fileName);
        }
        
        switch (choice) {
            case 1:
                puts("\n--------------------------------------------------------------------------------------------------------------------------------------\n");
                printf(ORANGE_TEXT "Enter the name of the target file: " RESET);
                scanf("%49s", fileName);
                printf(ORANGE_TEXT "Enter the name of the filter file: " RESET);
                scanf("%49s", filterName);
                theGreatFilter(fileName, filterName);
                puts(MAGENTA_BG "The target has been sanitized from the forbidden words succesfully" RESET);
                break;
            case 2:
                deleteEmptyLines(fileName);
                puts(MAGENTA_BG "The file has been sanitized from empty lines succesfully" RESET);
                break;
            case 3:
                sortLinesAlpha(fileName);
                puts(MAGENTA_BG "The file's lines have been sorted in alphabetical ascending order succesfully" RESET);
                break;
            case 0:
                return;
            default:
                continue;
        }
    }
}
