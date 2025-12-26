#ifndef __FILES__
#define __FILES__

/*Constants used throughout the project*/
#define MAXFILTER 500
#define MAXLENGTH 1024
#define MAXLINES 200

/*Color codes used to distinguish important output*/
// Background Highlights
#define MAGENTA_BG "\033[48;5;160m"  
#define RED_BG "\033[48;2;168;4;59m"

// Text Color
#define RED_TEXT "\033[38;5;197m"
#define ORANGE_TEXT "\033[38;5;203m"

// Reset Code (Must use this after every colored print)
#define RESET "\033[0m"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


/*Subject Handlers*/
void subjectOneHandler();
void subjectTwoHandler();
void subjectThreeHandler();
void subjectFourHandler();
void subjectFiveHandler();
void subjectSixHandler();

/*Utility functions*/
int isForbidden(char forbiddenList[MAXFILTER][MAXLENGTH], int filterCount, char buffer[]); 
void lowerBuffer(char buffer[]);
void swap(char **string1, char **string2);
int partitioner(char **lineArray, int lowIndex, int highIndex); 
void quickSortLines(char **lineArray, int lowIndex, int highIndex);
int palindromeSensor(char buffer[]);
int checkIfUnique(FILE *filePtr, char buffer[]); 

/*Subject 1*/
void deleteGivenChar(char fileName[], char target);
void lowerToUpper(char fileName[]);
void upperToLower(char fileName[]);
int countOccurence(char fileName[], char target[]);

/*Subject 2*/
int compareFiles(char fileName1[], char fileName2[]);
void concatenateFiles(char fileName1[], char fileName2[]);
void replaceGivenWord(char fileName[], char target[], char replacement[]);

/*Subject 3*/
void countLinesAndUniqueOccu(char fileName[]);
void inverseWords(char fileName[]);
void occurencesOverN(char fileName[], int n);

/*Subject 4*/
void detectPalindromes(char fileName[]);
void deleteNonAlph(char fileName[]);
void countGivenChar(char fileName[], char target);

/*Subject 5*/
void shortestAndLongestWord(char fileName[]);
void getAverageWordLength(char fileName[]);
void shortestAndLongestLine(char fileName[]);

/*Subject 6*/
void theGreatFilter(char targetFile[], char filterFile[]);
void deleteEmptyLines(char fileName[]);
void sortLinesAlpha(char fileName[]);

#endif
