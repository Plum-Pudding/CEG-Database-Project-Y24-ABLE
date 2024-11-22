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



//typedef STUDENTITEM_NODE *STUDENTITEM_NODE_PTR;

//// CREATE NEW NODE
//STUDENTITEM_NODE_PTR createNode(int id, const char *name, const char *programme, double grade) {
//    STUDENTITEM_NODE_PTR newNode = (STUDENTITEM_NODE_PTR)malloc(sizeof(STUDENTITEM_NODE));
//    if (newNode == NULL) {
//        printf("Memory allocation failed.\n");
//        exit(1);
//    }
//    newNode->ID = id;
//
//    strcpy(newNode->name, name);
//    strcpy(newNode->programme, programme);
//
//    newNode->grade = grade;
//    //newNode->next = NULL;
//
//    return newNode;
//}

int openFile(const char *filename) {
    STUDENTS student;
    /* open the file */
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }
    /* print header row */
    printf("%-10s\t%-20s\t%-30s\t%-10s\n", "ID", "Name", "Programme", "Grade");
    printf("----------------------------------------------------------------------------------------------\n");

    /* read until the end of the file */
    while (fscanf(file, "%d,%49[^,],%99[^,],%lf", &student.ID, student.name, student.programme, &student.grade) == 4) {
        /* print the student records */
        printf("%-10d\t%-20s\t%-30s\t%-10.2f\n", student.ID, student.name, student.programme, student.grade);
    }
    /* clean up*/
    fclose(file);
    return EXIT_SUCCESS;
}

int showAll(const char *filename) {
    if (openFile(filename) == EXIT_FAILURE) {
        printf("Error occurred while opening the file.\n");
    }
    return 0;
}

void insertStudent() {

}

void updateStudent() {

}

void deleteStudent() {

}

void saveDB() {

}

int main() {
    const char *filename = "P12_9-CMS.txt";
    char userInputRaw[MAX_UINPUT_LENGTH];

    /* opening declaration */
    printf("==========================================================================================\n");
    printf("\t\t\tDeclaration\n");
    printf("==========================================================================================\n");
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

    printf("Declared by: Group Name (please insert your group name)\n");

    
    
    
    return 0;
}

//void insertStudentAtStart(STUDENTITEM_NODE_PTR *head, STUDENTITEM_NODE_PTR newNode) {
//    newNode->next = *head;
//    *head = newNode;
//}
//
//void insertStudentAtEnd(STUDENTITEM_NODE_PTR* head, STUDENTITEM_NODE_PTR newNode) {
//    if (*head == NULL) {
//        *head = newNode;
//        return;
//    }
//
//    STUDENTITEM_NODE_PTR current = *head;
//    while (current->next != NULL) {
//        current = current->next;
//    }
//    current->next = newNode;
//}
//
//void insertStudentInOrder(STUDENTITEM_NODE_PTR* head, STUDENTITEM_NODE_PTR newNode) {
//    if (*head == NULL || strcmp(newNode->name, (*head)->name) < 0) {
//        insertStudentAtStart(head, newNode);
//        return;
//    }
//
//    STUDENTITEM_NODE_PTR current = *head;
//    while (current->next != NULL && strcmp(current->next->name, newNode->name) < 0) {
//        current = current->next;
//    }
//    
//    newNode->next = current->next;
//    current->next = newNode;
//}