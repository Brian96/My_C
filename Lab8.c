//
// APS105-F15 Lab 8 Lab8.c
//
// This is a program written to maintain a personal music library, 
// using a linked list to hold the songs in the library.
//
// Author: <Your Name Goes Here>
// Student Number: <Your Student Number Goes Here>
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

// A node in the linked list

// Each string in the node is declared as a character pointer variable,
// so they need to be dynamically allocated using the malloc() function,
// and deallocated using the free() function after use.

typedef struct node {
    char *songName;
    char *artist;
    char *genre;
    struct node *link;
} Node;

// Declarations of linked list functions
//
// Declare your own linked list functions here.
//
// ADD YOUR STATEMENT(S) HERE


// Declarations of support functions
// See below the main function for descriptions of what these functions do


bool checkDuplicate(char songName[]);
void insert(char son[], char art[], char gen[]);
void printList(void);
void search(char son[]);
void delete(char son[]);
void quit(void);

void getStringFromUserInput(char s[], int arraySize);
void songNameDuplicate(char songName[]);
void songNameFound(char songName[]);
void songNameNotFound(char songName[]);
void songNameDeleted(char songName[]);
void printMusicLibraryEmpty(void);
void printMusicLibraryTitle(void);

Node *head = NULL;
const int MAX_LENGTH = 1024;

bool checkDuplicate(char songName[]) {  // when duplicate return true
    Node *current = head;
    if (!head)
        return false;
    while (current != NULL) {
        if (strcmp(current -> songName, songName) == 0)
            return true;
        current = current -> link;
    }
    return false;
}

void insert(char son[], char art[], char gen[]) {
    Node *insert = (Node *) malloc(sizeof (Node));
    insert -> songName = (char *) malloc(MAX_LENGTH * sizeof (char));
    insert -> artist = (char *) malloc(MAX_LENGTH * sizeof (char));
    insert -> genre = (char *) malloc(MAX_LENGTH * sizeof (char));
    strcpy(insert -> songName, son);
    strcpy(insert -> artist, art);
    strcpy(insert -> genre, gen);
    Node *current = head;
    Node *prev = head;
    if (!head)
        head = insert;  //when head is null directly change head
    else if (strcmp(insert -> songName, head -> songName)<0){
        head = insert;
        head -> link = current; //when head is replaced
    }
    else {

        current = current -> link;
        while (current != NULL) {
            if (strcmp(current->songName, insert->songName) < 0) {
                prev = prev -> link;
                current = current -> link;     //go one step forward
            } else {
                prev -> link = insert;
                insert -> link = current;   //insert before current 
                return;
            }
        }
        prev -> link = insert;
        insert -> link = current;

    }
}


void printList(void) {
    Node *current = head;
    if (!head)
        printMusicLibraryEmpty();   // if nothing is in the linked list
    else {
        printMusicLibraryTitle();
        while (current != NULL) {
            printf("\n");
            printf("%s\n", current -> songName);
            printf("%s\n", current -> artist);
            printf("%s\n", current -> genre);
            current = current -> link;  //print out one by one until get to null
        }
    }
}

void search(char son[]) {
    Node *current = head;
    while (current != NULL) {
        if (strcmp(current -> songName, son) == 0) {
            songNameFound(son);
            printf("\n%s\n", son);
            printf("%s\n", current -> artist);
            printf("%s\n", current -> genre);
            return;
        } else
            current = current -> link;
    }

}

void delete(char son[]) {
    Node *current = head;
    Node *prev = head;
    Node *t;
    if (strcmp(head-> songName, son) == 0) {
        t = head;
        head = head->link;
        free(t->songName);
        free(t->artist);
        free(t->genre);
        free(t);    //when delete firstNode
    } else {
        current = head->link;
        while (current != NULL) {
            if (strcmp(current->songName, son) == 0) {
                prev->link = current->link;
                free(current->songName);
                free(current->artist);
                free(current->genre);
                free(current);
                return;
            } else {
                prev = prev -> link;
                current = current->link;    //when delete following node
            }

        }
    }
}

void quit(void) {
    Node *current = head;
    while (current != NULL) {
        Node *t;
        songNameDeleted(current -> songName);
        t = current;
        current = current -> link;
        free(t -> songName);
        free(t -> artist);
        free(t -> genre);
        free(t);    //free until meet null
    }
    printMusicLibraryEmpty();
}

int main(void) {
    // Declare the head of the linked list.

    //   ADD YOUR STATEMENT(S) HERE

    // Announce the start of the program
    printf("%s", "Personal Music Library.\n\n");
    printf("%s", "Commands are I (insert), D (delete), S (search by song name),\n"
            "P (print), Q (quit).\n");

    char response;
    char input[MAX_LENGTH + 1];
    do {
        printf("\nCommand?: ");
        getStringFromUserInput(input, MAX_LENGTH);

        // Response is the first character entered by user.
        // Convert to uppercase to simplify later comparisons.
        response = toupper(input[0]);

        if (response == 'I') {
            // Insert a song into the linked list.
            // Maintain the list in alphabetical order by song name.
            //   ADD STATEMENT(S) HERE

            // USE THE FOLLOWING PRINTF STATEMENTS WHEN PROMPTING FOR DATA:
            // printf("Song name: ");
            // printf("Artist: ");
            // printf("Genre: ");
            char son[MAX_LENGTH + 1], art[MAX_LENGTH + 1], gen[MAX_LENGTH + 1];
            printf("Song name: ");
            getStringFromUserInput(son, MAX_LENGTH);
            printf("Artist: ");
            getStringFromUserInput(art, MAX_LENGTH);
            printf("Genre: ");
            getStringFromUserInput(gen, MAX_LENGTH);
            if (checkDuplicate(son) == true)
                songNameDuplicate(son);
            else
                insert(son, art, gen);

        } else if (response == 'D') {
            // Delete a song from the list.
            char deleSon[MAX_LENGTH + 1];
            printf("\nEnter the name of the song to be deleted: ");
            getStringFromUserInput(deleSon, MAX_LENGTH);
            if (checkDuplicate(deleSon) == false)
                songNameNotFound(deleSon);
            else {
                delete(deleSon);
                songNameDeleted(deleSon);
            }
            //   ADD STATEMENT(S) HERE

        } else if (response == 'S') {
            // Search for a song by its name.
            char searSon[MAX_LENGTH + 1];
            printf("\nEnter the name of the song to search for: ");
            getStringFromUserInput(searSon, MAX_LENGTH);
            if (checkDuplicate(searSon) == false)
                songNameNotFound(searSon);
            else
                search(searSon);
            //   ADD STATEMENT(S) HERE

        } else if (response == 'P') {
            // Print the music library.
            printList();
            //   ADD STATEMENT(S) HERE

        } else if (response == 'Q') {
            // do nothing, we'll catch this below
            quit();
        } else {
            // do this if no command matched ...
            printf("\nInvalid command.\n");
        }
    } while (response != 'Q');

    // Delete the entire linked list.
    //   ADD STATEMENT(S) HERE

    // Print the linked list to confirm deletion.
    //   ADD STATEMENT(S) HERE

    return 0;
}

// Support Function Definitions

// Prompt the user for a string safely, without buffer overflow

void getStringFromUserInput(char s[], int maxStrLength) {
    int i = 0;
    char c;

    while (i < maxStrLength && (c = getchar()) != '\n')
        s[i++] = c;

    s[i] = '\0';
}

// Function to call when the user is trying to insert a song name 
// that is already in the personal music library.

void songNameDuplicate(char songName[]) {
    printf("\nA song with the name '%s' is already in the music library.\n"
            "No new song entered.\n", songName);
}

// Function to call when a song name was found in the personal music library.

void songNameFound(char songName[]) {
    printf("\nThe song name '%s' was found in the music library.\n",
            songName);
}

// Function to call when a song name was not found in the personal music library.

void songNameNotFound(char songName[]) {
    printf("\nThe song name '%s' was not found in the music library.\n",
            songName);
}

// Function to call when a song name that is to be deleted
// was found in the personal music library.

void songNameDeleted(char songName[]) {
    printf("\nDeleting a song with name '%s' from the music library.\n",
            songName);
}

// Function to call when printing an empty music library.

void printMusicLibraryEmpty(void) {
    printf("\nThe music library is empty.\n");
}

// Function to call to print a title when the entire music library is printed.

void printMusicLibraryTitle(void) {
    printf("\nMy Personal Music Library: \n");
}

// Add your functions below this line.

//   ADD STATEMENT(S) HERE