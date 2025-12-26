#include <files.h>

int main(void) {
    int choice = 0;

    puts(RED_BG "\nWelcome to my file handling menu! Choose a subject to proceed:" RESET);
    while(1) {
        puts("\n--------------------------------------------------------------------------------------------------------------------------------------\n");
        puts(RED_TEXT"--> Select 1 for subject 1");
        puts("--> Select 2 for subject 2");
        puts("--> Select 3 for subject 3");
        puts("--> Select 4 for subject 4");
        puts("--> Select 5 for subject 5");
        puts("--> Select 6 for subject 6");
        puts("--> Select 0 to close the program!");
        printf("\nYour choice is: " RESET);
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                subjectOneHandler();
                break;
            case 2:
                subjectTwoHandler();
                break;
            case 3:
                subjectThreeHandler();
                break;
            case 4:
                subjectFourHandler();
                break;
            case 5:
                subjectFiveHandler();
                break;
            case 6:
                subjectSixHandler();
                break;
            case 0:
                return 0;
            default:
                continue;
        }
    }
}
