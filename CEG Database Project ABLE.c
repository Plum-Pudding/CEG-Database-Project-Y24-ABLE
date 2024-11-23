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
#define QUERY "QUERY ID"
#define UPDATE "UPDATE"
#define DELETE "DELETE"
#define SAVE "SAVE"
#define END_MY_SUFFERING "EXIT" 

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
    printf("----------------------------------------------------------------------------------------------\n");

    /* to reset the file pointer to the beginning before reading */
    rewind(file);
    
    /* read until the end of the file */
    while (fscanf(file, "%d,%49[^,],%99[^,],%lf", &student.ID, student.name, student.programme, &student.grade) == 4) {
        /* print the student records */
        printf("%-10d\t%-20s\t%-30s\t%-10.2f\n", student.ID, student.name, student.programme, student.grade);
    }
    return EXIT_SUCCESS;
}

int checkStudentID(FILE *file, int ID) {
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

int insertStudent(FILE* file, const char *filename, int ID, const char *name, const char *programme, double grade) {
    STUDENTS student;

    /* rewind the pointer to check for duplicates */
    rewind(file);

    while (fscanf(file, "%d,%49[^,],%99[^,],%lf", &student.ID, student.name, student.programme, &student.grade) == 4) {
        if (student.ID == ID) {
            printf("CMS: The record with ID=%d already exists.", ID);
            return EXIT_FAILURE;
        }
    }

    /* close the file for reading and reopen in append mode */ 
    fclose(file);
    file = fopen(filename, "a");
    if (!file) {
        perror("CMS: Failed to open file for appending");
        return EXIT_FAILURE;
    }

    /* append the new student record to the file */
    fprintf(file, "%d,%s,%s,%.2f\n", ID, name, programme, grade);
    printf("CMS: A new record with ID=%d is successfully inserted.\n", ID);

    /* close after appending */
    fclose(file);

    return EXIT_SUCCESS;
}

int queryStudent(FILE *file, int ID) {
    STUDENTS student;
    int found = 0; // flag if ID is found or not

    /* ensure file pointer is at the beginning */
    rewind(file);

    while (fscanf(file, "%d, %49[^,], %99[^,], %lf", &student.ID, student.name, student.programme, &student.grade) == 4) {
        if (student.ID == ID) {
            printf("CMS: The record with ID=%d is found in the data table.\n", ID);
            printf("%-10s\t%-20s\t%-30s\t%-10s\n", "ID", "Name", "Programme", "Grade");
            printf("----------------------------------------------------------------------------------------------\n");
            printf("%-10d\t%-20s\t%-30s\t%-10.2f\n", student.ID, student.name, student.programme, student.grade);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("CMS: The record with ID=%d does not exist.\n", ID);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int updateStudent(FILE* file, const char *filename, int ID, const char *field, const char *newValue) {
    STUDENTS student;
    int found = 0;

    /* Open a temporary file to rewrite the data */
    FILE* tempFile = fopen("temp.txt", "w");
    if (!tempFile) {
        perror("Failed to open temporary file");
        return EXIT_FAILURE;
    }

    /* Start from beginning of the file */
    rewind(file);

    /* Read each record and update if ID matches */
    while (fscanf(file, "%d,%49[^,],%99[^,],%lf", &student.ID, student.name, student.programme, &student.grade) == 4) {
        if (student.ID == ID) {
            found = 1;
        
            // update the appropriate field
            if (strcmp(field, "NAME") == 0) {
                strncpy(student.name, newValue, sizeof(student.name) - 1);
            }
            else if (strcmp(field, "PROGRAMME") == 0) {
                strncpy(student.programme, newValue, sizeof(student.programme) - 1);
            }
            else if (strcmp(field, "GRADE") == 0) {
                student.grade = atof(newValue); // convert string to double
            }
            else {
                printf("Error: Invalid field '%s'. Allowed fields: Name, Programme, Grade.", field);
                fclose(tempFile);
                return EXIT_FAILURE;
            }
        }
        /* write the record (updated or unchanged) to the temporary file */
        fprintf(tempFile, "%d,%s,%s,%.2f\n", student.ID, student.name, student.programme, student.grade);
    }

    fclose(file);       // close the original file 
    fclose(tempFile);   // close the temporary file

    /* replace the original file with the updated file */
    if (found) {
        remove(filename);   // delete the og file
        rename("temp.txt", filename);   // rename the temporary file to the original name
        file = fopen(filename, "r");    // reopen the updated file in read mode
        if (!file) {
            perror("Failed to reopen updated file.\n");
            return EXIT_FAILURE;
        }
    }
    else {
        printf("CMS: The record with ID=%d does not exist.\n", ID);
        remove("temp.txt"); // cleanup temporary file
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;

}

int deleteStudent(FILE* file, const char *filename, int ID) {
    STUDENTS student;
    int found = 0;

    /* open a temporary file to rewrite data excluding the target record */
    FILE* tempFile = fopen("temp.txt", "w");
    if (!tempFile) {
        printf("CMS: Failed to open temporary file.\n");
        return EXIT_FAILURE;
    }

    /* reset the pointer to the beginning as always */
    rewind(file);
    
    /* read each record */
    while (fscanf(file, "%d,%49[^,],%99[^,],%lf", &student.ID, student.name, student.programme, &student.grade) == 4) {
        if (student.ID == ID) {
            found = 1;

            char choice[10];
            printf("Are you sure you want to delete record with ID=%d? Type \"Y\" to Confirm or type \"N\" to cancel.\n", ID);
            fgets(choice, sizeof(choice), stdin);
            choice[strcspn(choice, "\n")] = 0;  // remove newline character

            if (strcmp(choice, "Y") == 0 || strcmp(choice, "y") == 0) {
                printf("CMS: The record with ID=%d is successfully deleted.\n", ID);
                continue;
            }
            else if (strcmp(choice, "N") == 0 || strcmp(choice, "n") == 0) {
                printf("CMS: The deletion is cancelled.\n");
            }
        }

        /* write all other records to the temporary file */
        fprintf(tempFile, "%d,%s,%s,%.2f\n", student.ID, student.name, student.programme, student.grade);
    }

    fclose(file);
    fclose(tempFile);

    /* handle cases where ID not found */
    if (!found) {
        remove("temp.txt");
        return EXIT_FAILURE;
    }

    /* replace original file with the updated file */
    remove(filename);
    if (rename("temp.txt", filename) != 0) {
        perror("CMS: Failed to update the file.\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
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
            printf("CMS: Wrong input bro\n");
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
            printf("CMS: Unknown command: %s\n", userInputRaw);
        }
    }

    /* loop to handle next commands */
    while (1) {
        printf("\n");
        printf("TYPE A COMMAND:\n");
        printf("%-15s%-15s%-15s%-15s%-15s%-15s%-15s\n", "SHOW ALL", "INSERT", "QUERY", "UPDATE", "DELETE", "SAVE", "EXIT");
        printf("\n");

        if (fgets(userInputRaw, sizeof(userInputRaw), stdin) == NULL) {
            printf("Invalid command try again.\n");
            continue;
        }

        userInputRaw[strcspn(userInputRaw, "\n")] = 0;

        /* EXIT */
        if (strcmp(userInputRaw, END_MY_SUFFERING) == 0) {
            printf("goodbye!\n");
            break;
        }

        /* SHOW ALL */
        if (strcmp(userInputRaw, SHOWALL) == 0) {
            if (showAll(file) == EXIT_FAILURE) {
                printf("Error displaying database.\n");
            }
        }

        /* INSERT */
        if (strcmp(userInputRaw, INSERT) == 0) {
            int ID;
            char name[MAX_NAME_LENGTH];
            char programme[MAX_PROGRAMME_LENGTH];
            double grade;

            printf("INSERT ID=");
            if (scanf("%d", &ID) != 1 || ID < 2000000 || ID > 2999999) {
                printf("Error: ID must be 7 digits and according to SIT format.\n");
                while (getchar() != '\n'); // cldear invalid input
                continue;
            }
            while (getchar() != '\n');

            if (checkStudentID(file, ID) == EXIT_FAILURE) {
                continue;
            }

            /* NAME */
            printf("Name=");
            if (fgets(name, MAX_NAME_LENGTH, stdin) == NULL || name[0] == '\n') {
                printf("Error: Invalid name.\n");
                continue;
            }
            name[strcspn(name, "\n")] = 0; // remove newline character

            /* PROGRAMME */
            printf("Programme=");
            if (fgets(programme, MAX_PROGRAMME_LENGTH, stdin) == NULL || programme[0] == '\n') {
                printf("Error: Invalid programme.\n");
                continue;
            }
            programme[strcspn(programme, "\n")] = 0;

            /* GRADE */
            printf("Grade=");
            if (scanf("%lf", &grade) != 1 || grade < 0.0 || grade > 100.0) {
                printf("Error: Invalid grade. Please enter a value between 0 - 100.\n");
                while (getchar() != '\n');
                continue;
            }
            while (getchar() != '\n'); // clear leftover newline

            /* Call insertStudent to handle inserting of student */
            if (insertStudent(file, filename, ID, name, programme, grade) == EXIT_FAILURE) {
                printf("CMS: Failed to insert the student. Please try again.\n");
            }
            else {
                /* Reopen file in read mode */
                file = fopen(filename, "r");
                if (!file) {
                    perror("CMS: Failed to reopen file after appending.\n");
                    return EXIT_FAILURE;
                }
            }
            continue;
        }

        /* QUERY */
        if (strncmp(userInputRaw, "QUERY ID=", 9) == 0) {
            int ID;

            if (sscanf(userInputRaw + 9, "%d", &ID) != 1 || ID < 2000000 || ID > 2999999) {
                printf("Error: ID must be 7 digits and according to SIT format.\n");
                continue;
            }

            if (queryStudent(file, ID) == EXIT_FAILURE) {
                continue;
            }
            continue;
        }


        /* UPDATE */
        if (strncmp(userInputRaw, "UPDATE ID=", 10) == 0) {
            int ID;
            char field[50] = { 0 };
            char newValue[100] = { 0 };

            /* Extract ID */
            if (sscanf(userInputRaw + 10, "%d", &ID) != 1 || ID < 2000000 || ID > 2999999) {
                printf("Error: ID must be 7 digits and according to SIT format.", ID);
                continue;
            }

            /* Extract field to update its new value */
            char* fieldStart = strchr(userInputRaw + 10, ' '); // find the space after the ID
            if (!fieldStart || sscanf(fieldStart + 1, "%49[^=]=%99[^\n]", field, newValue) != 2) {
                printf("Error: Invalid format. Use UPDATE ID=XXXXXXX Field=Value.\n");
                continue;
            }

            /* Update the record */
            if (updateStudent(file, filename, ID, field, newValue) == EXIT_FAILURE) {
                printf("CMS: Failed to update the record for ID=%d", ID);
            }
            else {
                printf("CMS: The record with ID=%d is successfully updated.", ID);
            }
            continue;
        }


        /* DELETE */
        if (strncmp(userInputRaw, "DELETE ID=", 10) == 0) {
            int ID;

            if (sscanf(userInputRaw + 10, "%d", &ID) != 1 || ID < 2000000 || ID > 2999999 ){
                printf("Error: ID must be 7 digits and according to SIT format.", ID);
                continue;
            }

            /* extract ID */
            if (deleteStudent(file, filename, ID) == EXIT_FAILURE) {
                printf("CMS: The record with ID=%d does not exist.\n", ID);

                // reopen the file in read mode to ensure subsequent commands work
                file = fopen(filename, "r");
                if (!file) {
                    perror("CMS: Failed to reopen the updated file.\n");
                    return EXIT_FAILURE;
                }
            }
            else {
                file = fopen(filename, "r");
                if (!file) {
                    perror("CMS: Failed to reopen the updated file.\n");
                    return EXIT_FAILURE;
                }
            }
            continue;
        }

        /* SAVE */
        if (strcmp(userInputRaw, SAVE) == 0) {
            printf("SAVING SOMETHING????\n");
            continue;
        }
        
    }

    if (file) {
        fclose(file);
    }

    return 0;
}
