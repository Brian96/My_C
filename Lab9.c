//
//  main.c
//  Lab9
//
//  Created by mac on 2015-11-30.
//  Copyright (c) 2015 mac. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

const int MAX_LENGTH = 1024;
const int MAX_LIBRARY_SIZE = 100;

typedef struct song
{
    char songName[MAX_LENGTH];
    char artist[MAX_LENGTH];
} Song;

Song Library[MAX_LIBRARY_SIZE];


void getStringFromUserInput(char s[], int maxStrLength);
void insert(char songName[], char artist[], int i);
void printList(int i);
void cocktailSort(Song library[], int size);;
void printMusicLibraryEmpty(void);
void printMusicLibraryTitle(void);
bool inOrder(Song Library[], int i);
int main(void) {
    printf("%s", "Personal Music Library.\n\n");
    printf("%s", "Commands are I (insert), S (sort by artist),\n"
           "P (print), Q (quit).\n");
    int i = 0;
    char response;
    char input[MAX_LENGTH + 1];
    do {
        printf("\nCommand?: ");
        getStringFromUserInput(input, MAX_LENGTH);
        response = toupper(input[0]);
        
        if (response == 'I') {
            char son[MAX_LENGTH], art[MAX_LENGTH];
            printf("Song name: ");
            getStringFromUserInput(son, MAX_LENGTH);
            printf("Artist: ");
            getStringFromUserInput(art, MAX_LENGTH);
            insert(son, art, i);
            i++;
        }
        else if (response == 'S') {
            cocktailSort(Library, i);
            
        }
        else if (response == 'P') {
            printList(i);
            
        }
        else if (response == 'Q') {
            ;
        }
        else {
            // do this if no command matched ...
            printf("\nInvalid command.\n");
        }
    } while (response != 'Q');
    return 0;
}

void getStringFromUserInput(char s[], int maxStrLength) {
    int i = 0;
    char c;
    
    while (i < maxStrLength && (c = getchar()) != '\n')
        s[i++] = c;
    
    s[i] = '\0';
}

void insert(char songName[], char artist[], int i){
    strcpy(Library[i].songName, songName);
    strcpy(Library[i].artist, artist);
}

void printList(int i){
    int a = 0;
    if(i == 0){
        printMusicLibraryEmpty();
    }
    else{
        printMusicLibraryTitle();
        while(a<i){
            printf("\n%s\n", Library[a].songName);
            printf("%s\n", Library[a].artist);
            a++;
        }
    }
}

void cocktailSort(Song library[], int size){
    int direction = 1;
    int i = size;
    if (i == 0){
        printMusicLibraryEmpty();
    }
    else{
        while (inOrder(Library, i)==false){
            int a;
            if (direction > 0){
                a = 0;
                while (a<i-1){
                    if(strcmp (Library[a].artist, Library[a+1].artist) < 0)
                        a++;
                    else if(strcmp(Library[a].artist, Library[a+1].artist) == 0){
                        if (strcmp(Library[a].songName, Library[a+1].songName) <= 0)
                            a++;
                        else{
                            Song temp;
                            temp = Library[a];
                            Library[a] = Library[a+1];
                            Library[a+1] = temp;
                        }
                    }
                    else{
                        Song temp;
                        temp = Library[a];
                        Library [a] = Library[a+1];
                        Library [a+1] = temp;
                    }
                }
            }
            else if(inOrder(Library, i)==false){
                ;
            }
            else if (direction <0){
                a = i-1;
                while (a>0){
                    if(strcmp (Library[a].artist, Library[a-1].artist) > 0)
                        a++;
                    else if(strcmp(Library[a].artist, Library[a-1].artist) == 0){
                        if (strcmp(Library[a].songName, Library[a-1].songName) >= 0)
                            a++;
                        else{
                            Song temp;
                            temp = Library[a];
                            Library[a] = Library[a-1];
                            Library[a-1] = temp;
                        }
                    }
                    else{
                        Song temp;
                        temp = Library[a];
                        Library [a] = Library[a-1];
                        Library [a-1] = temp;
                    }
                }
            }
            direction *= -1;
        }
        printList(i);
    }
}

void printMusicLibraryEmpty(void)
{
    printf("\nThe music library is empty.\n");
}

void printMusicLibraryTitle(void){
    printf("\nMy Personal Music Library: \n");
}

bool inOrder(Song Library[], int i){
    int a = 0;
    if (i == 1)
        return true;
    while (a<i-1){
        if (strcmp(Library[a].artist, Library[a+1].artist)<0)
            a++;
        else if (strcmp(Library[a].artist, Library[a+1].artist)==0){
            if (strcmp(Library[a].songName, Library[a+1].songName)<=0)
                a++;
            else
                return false;
        }
        else
            return false;
    }
    return true;
}
