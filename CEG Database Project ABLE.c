#include <stdio.h>
#include <string.h>

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

struct studentItem {
    int ID;
    char name[MAX_NAME_LENGTH];
    char programme[MAX_PROGRAMME_LENGTH];
    double grade;
};

void showALl() {

}

void insertStudent() {

}

void queryID() {

}

void updateStudent() {

}

void deleteStudent() {

}

void saveDB() {

}

int main() {
    char userInputRaw[MAX_UINPUT_LENGTH];


    //main loop
    while (1) {



        break;
    }
    return 0;
}
