#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_UINPUT_LENGTH 255
#define MAX_NAME_LENGTH 255
#define MAX_PROGRAMME_LENGTH 255
#define SANITY -999
#define CIGARETTES 500
#define ID_LEN 7

#define OPENFILE "OPEN"
#define SHOWALL "SHOW ALL"
#define INSERT "INSERT"
#define QUERY "QUERY"
#define UPDATE "UPDATE"
#define DELETE "DELETE"
#define SAVE "SAVE"
#define END_MY_SUFFERING "***" 

//TODO: make a command detection function-- takes string (user inputted command) as input, returns an int corresponding to command-- see below
//TODO: main loop contains an perpetual loop
//TODO: func to read text file into memory-- this part sucks
//TODO: switch statement takes int returned by command function, executes appropriate function and passes user input as string parameter to be parsed 
//TODO: functions for each command
//TODO: function to output 1 line nicely formatted
//TODO: XD LOOK HERE pls advise if we should break this up and put some util functions in another file-- I don't think it's necessary personally since it's not a bit program
//TODO: Should we use a linked list to store this db in memory??? -- I feel we have three options: 2D array, array of (row)structs, linked list using structs-- I'm most inclined to array of structs
//TODO: ^ Depends on performance priority-- Linked list will be slow for indexing, but fast to insert rows in the middle of the list. 
//TODO: Array of structs will be fast(er) to index and search the spec doesn't require db to be sorted so we can just stick on new rows to the end
//TODO: Will need to sort array if we want to use fast search algorithms though.

/* Creating student struct for student attributes */
typedef struct student_struct {
    int ID;
    char name[MAX_NAME_LENGTH];
    char programme[MAX_PROGRAMME_LENGTH];
    double grade;
    //struct studentItem *next;
} STUDENTS;


int interpretCommand(char* rawUserInput, int inputLength) {
    int commandIndex = -1;                          //default value (if no valid command found in user input, return -1)
    char trimmedUserInput[MAX_UINPUT_LENGTH];       //

    //TODO: cut out the chars before the first encountered whitespace ' '
    for (int i = 0; i < MAX_UINPUT_LENGTH; i++) {
        if (rawUserInput[i] == ' ') {
            //whitespace found-- stop the loop
            break;
        }
        else {
            trimmedUserInput[i] = rawUserInput[i];
        }
    }

    //Yes I know-- this is catastrophically bad lol
    if (/*OPEN*/ 1) {
        commandIndex = 1;
    }
    else if (/*INSERT*/ 1) {
        commandIndex = 2;
    }
    else if (/*QUERY*/ 1) {
        commandIndex = 3;
    }
    else if (/*UPDATE*/ 1) {
        commandIndex = 4;
    }
    else if (/*DELETE*/ 1) {
        commandIndex = 5;
    }
    else if (/*SAVE*/ 1) {
        commandIndex = 6;
    }
    else if (/*SHOW ALL*/ 1) {
        commandIndex = 7;
    }

    return commandIndex; //TODO: check if we should just return() in the if else chain-- I don't think it matters
}


FILE* openFile(const char *filename) {
    /* open the file */
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        return NULL;
    }
    return file;
}

int showAll(FILE* file) {
    STUDENTS student;
    
    if (!file) {
        perror("Failed to open file.");
        return EXIT_FAILURE;
    }

    /* print header row */
    printf("CMS: Here are all the records found in the table \"StudentRecords\"\n");
    printf("%-10s\t%-20s\t%-30s\t%-10s\n", "ID", "Name", "Programme", "Grade");
    printf("-----------------------------------------------------------------------------------\n");

    /* to reset the file pointer to the beginning before reading */
    rewind(file);
    
    /* read until the end of the file */
    while (fscanf(file, "%d,%49[^,],%99[^,],%lf", &student.ID, student.name, student.programme, &student.grade) == 4) {
        /* print the student records */
        printf("%-10d\t%-20s\t%-30s\t%-10.2f\n", student.ID, student.name, student.programme, student.grade);
    }
    return EXIT_SUCCESS;
}

int checkStudentID(FILE* file, int ID) {
    STUDENTS student;

    rewind(file);
    while (fscanf(file, "%d, %49[^,], %99[^,],%lf", &student.ID, student.name, student.programme, &student.grade) == 4) {
        if (student.ID == ID) {
            printf("CMS: The record with ID=%d already exists.", ID);
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
    
}

FILE* insertStudent(FILE* file, const char *filename, int ID, const char *name, const char *programme, double grade) {
    STUDENTS student;

    /* rewind the pointer to check for duplicates */
    rewind(file);

    while (fscanf(file, "%d,%49[^,],%99[^,],%lf", &student.ID, student.name, student.programme, &student.grade) == 4) {
        if (student.ID == ID) {
            printf("CMS: The record with ID=%d already exists.", ID);
            return file;
        }
    }

    /* close the file for reading and reopen in append mode */ 
    fclose(file);
    file = fopen(filename, "a");
    if (!file) {
        perror("Failed to open file for appending");
        return NULL;
    }

    /* append the new student record to the file */
    fprintf(file, "%d,%s,%s,%.2f\n", ID, name, programme, grade);
    printf("CMS: A new record with ID=%d is successfully inserted.\n", ID);

    /* close after appending */
    fclose(file);

    /* Reopen file in read mode */
    file = fopen(filename, "r");
    if (!file) {
        perror("Failed to reopen file after appending.");
        return NULL;
    }
    return file;
}

void updateStudent() {

}

void deleteStudent() {

}

void saveDB() {

}

int main() {
    const char *filename = "P12_9-CMS.txt";
    char userInputRaw[MAX_UINPUT_LENGTH + 1];
    FILE* file = NULL;

    int fileOpened = 0; // flag to check if file opened
    int idPass = 0; 

    /* opening declaration */
    printf("*                       *   **************  *                **************   **************  *                * **************\n");
    printf(" *                     *    *               *                *                *            *  * *             ** *             \n");
    printf("  *                   *     *               *                *                *            *  *  *           * * *             \n");
    printf("   *                 *      *               *                *                *            *  *   *         *  * *             \n");
    printf("    *       *       *       **************  *                *                *            *  *    *       *   * **************\n");
    printf("     *     * *     *        *               *                *                *            *  *     *     *    * *             \n");
    printf("      *   *   *   *         *               *                *                *            *  *      *   *     * *             \n");
    printf("       * *     * *          *               *                *                *            *  *       * *      * *             \n");
    printf("        *       *           **************  ***************  **************   **************  *        *       * **************\n\n\n");
    printf("\033[0;32m");
    printf("==================================================================\n");
    printf("\t\t\tDeclaration\n");
    printf("==================================================================\n");
    printf("\033[0;0m"); 
    printf("SIT's policy on copying does not allow the students to copy source\n");
    printf("code as well as assessment solutions from another person or other\n");
    printf("places. It is the students' responsibility to guarantee that their\n");
    printf("assessment solutions are their own work. Meanwhile, the students\n");
    printf("must also ensure that their work is not accessible by others. Where\n");
    printf("such plagiarism is detected, both of the assessments involved will\n");
    printf("receive ZERO marks.\n\n");

    printf("We hereby declare that:\n");
    printf("  * We fully understand and agree to the abovementioned plagiarism policy.\n");
    printf("  * We did not copy any code from others or from other places.\n");
    printf("  * We did not share our codes with others or upload to any other places\n");
    printf("    for public access and will not do that in the future.\n");
    printf("  * We agree that our project will receive Zero mark if there is any\n");
    printf("    plagiarism detected.\n");
    printf("  * We agree that we will not disclose any information or material of the\n");
    printf("    group project to others or upload to any other places for public access.\n\n");

    printf("Declared by: Group Name (P12_9)\n");
    printf("James\n");
    printf("Hanif\t2401048\n");
    printf("Kugan\t2401294\n");
    printf("Wei Xiang\n");
    printf("Justin\n");
    printf("Xuande\n");

    printf("====================================================================================\n");

    /* loop to handle "OPEN" command */
    while (!file) {
        printf("\n");
        printf("Type OPEN to open the student database.\n");
        printf("\n");

        if (fgets(userInputRaw, sizeof(userInputRaw), stdin) == NULL) {
            printf("Wrong input bro\n");
            return 1;
        }

        userInputRaw[strcspn(userInputRaw, "\n")] = 0;

        if (strcmp(userInputRaw, END_MY_SUFFERING) == 0) {
            printf("goodbye!\n");
            return 0;
        }
        
        if (strcmp(userInputRaw, OPENFILE) == 0) {
            file = openFile(filename);
            if (file) {
                printf("CMS: The database file %s is successfully opened.\n", filename);
                memset(userInputRaw, 0, sizeof(userInputRaw));
            }
            else {
                printf("Failed to open database file. Try again.\n");
            }
        }
        else {
            printf("Unknown command: %s\n", userInputRaw);
        }
    }

    /* loop to handle next commands */
    while (1) {
        printf("\n");
        printf("TYPE A COMMAND:\n");
        printf("%-15s%-15s%-15s%-15s%-15s%-15s\n", "SHOW ALL", "INSERT", "QUERY", "UPDATE", "DELETE", "SAVE");
        printf("\n");

        if (fgets(userInputRaw, sizeof(userInputRaw), stdin) == NULL) {
            printf("Invalid command try again.\n");
            continue;
        }

        userInputRaw[strcspn(userInputRaw, "\n")] = 0;

        if (strcmp(userInputRaw, END_MY_SUFFERING) == 0) {
            printf("goodbye!\n");
            break;
        }

        if (strcmp(userInputRaw, SHOWALL) == 0) {
            if (showAll(file) == EXIT_FAILURE) {
                printf("Error displaying database.\n");
            }
        }
        /*else {
            printf("Unknown bro: %s\n", userInputRaw);
        }*/

        if (strncmp(userInputRaw, INSERT, strlen(INSERT)) == 0) {
            int ID;
            char name[MAX_NAME_LENGTH] = {0};
            char programme[MAX_PROGRAMME_LENGTH] = {0};
            double grade;


            if (ID < 2000000 || ID > 2900000) {
                printf("Error: ID must be 7 digits and according to SIT format.\n");
                continue;
            }

            if (insertStudent(file, filename, ID, name, programme, grade) == EXIT_FAILURE) {
                printf("Failed to insert the student. Try again.\n");
            }
            
        }
        
    }

    if (file) {
        fclose(file);
    }

    return 0;
}
