/* 
 * File:   Lab7.c
 * Author: weiliche
 *
 * Created on November 9, 2015, 3:28 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/*
 * 
 */
void printBoard(char board[26][26], int n);
bool positionInBounds(int N, char row, char col);
bool checkLegalInDirection(char board[26][26], int N, char row, char col, char colour, int deltaRow, int deltaCol);
void flip(int dimension, char board[26][26], char colour, char row, char col, int deltaRow, int deltaCol);
void filpAllAfterLegal(int dimension, char board[26][26], char colour, char row, char col);
bool checkLegal(int dimension, char board[26][26], char row, char col, char colour);
bool haveMove(int dimension, char board[26][26], char colour);
void finalCompare(int dimension, char board[26][26], char colour, char diffColour);
int score(int dimension, char board[26][26], char colour, int i, int j);
void scoreBoard(int dimension, char board[26][26], int copy[26][26], char colour);
void changeBestMove(int dimension, char board[26][26], int copy[26][26], char colour);
//identify names of functions at the start of whole program

void printBoard(char board[26][26], int n){
    int i,j;
    char firstRow, firstCol;
    firstRow = 'a';
    firstCol = 'a';
    printf("  ");
    for(i=0;i<n;i++){
        printf("%c",firstRow);
        firstRow++;
    }
    printf("\n");   //first row of print finish
    for(i=0;i<n;i++){
        printf("%c ", firstCol);
        firstCol++;
        for (j=0;j<n;j++)
            printf("%c",board[i][j]);
        printf("\n");   //print according to the array input row by row
    }
}

bool positionInBounds(int N, char row, char col){
    if ((N>(row-'a'))&&(N>(col-'a')))   
        return true;
    else
        return false;   //return false when point is out of the dimension
}

bool checkLegalInDirection(char board[26][26], int N, char row, char col, char colour, int deltaRow, int deltaCol)
{
    char sameColour, diffColour;
    if (colour == 'W')
    {
        sameColour = 'W';
        diffColour = 'B';
    }
    else if (colour == 'B')
    {
        sameColour = 'B';
        diffColour = 'W';   //this allows the function to apply on both colors
    }
    int i,j;
    i = row - 'a';
    j = col - 'a';
    int counter=0;
    i += deltaRow;
    j += deltaCol;
    if((i<0)||(j<0)||(i>=N)||(j>=N))
        return false;   //when the first move gets out of the boundary
    else if (board[i][j]==sameColour)
        return false;   //when the first move is the same color
    else if (board[i][j]=='U')
        return false;   //when the first move is unoccupied
    else
    {
        while((i>=0)&&(j>=0)&&(i<N)&&(j<N))
        {
            i+=deltaRow;
            j+=deltaCol;
            if(board[i][j]==sameColour)
                return true;    //when the end of different colors is the same color
            else if(board[i][j]=='U')
                return false;   //when the end of different colors is unoccupied
            else
                counter++;  //counter does not work in lab 6, it is prepared for lab 7
        }
        return false;   //when gets out of the boundary
    }  
}



void flip(int dimension, char board[26][26], char colour, char row, char col, int deltaRow, int deltaCol){
    char sameColour, diffColour;    //the function only flip and not judge whether the move is available or not
    if (colour == 'W')              
    {
        sameColour = 'W';
        diffColour = 'B';
    }
    else if (colour == 'B')
    {
        sameColour = 'B';
        diffColour = 'W';
    }
    int i,j;
    i = row - 'a';
    j = col - 'a';
    board[i][j] = colour;   //flip the origin move
    i+=deltaRow;
    j+=deltaCol;
    while (board[i][j]==diffColour){
        board[i][j]=sameColour; //flip the following moves one by one
        i+=deltaRow;
        j+=deltaCol;
    }
}

void flipAllAfterLegal(int dimension, char board[26][26], char colour, char row, char col){
    int deltaRow, deltaCol;
    for(deltaRow=-1;deltaRow<=1;deltaRow++){
        for(deltaCol=-1;deltaCol<=1;deltaCol++){
            if ((deltaRow!=0)||(deltaCol!=0)){
                if (checkLegalInDirection(board, dimension, row, col, colour, deltaRow, deltaCol) == true){
                    flip(dimension, board, colour, row, col, deltaRow, deltaCol);
                }
            }
        }
    }
}

bool checkLegal(int dimension, char board[26][26], char row, char col, char colour){
    bool legal = false;
    int deltaRow, deltaCol;
    if (positionInBounds(dimension, row, col)==false){
        return legal;
    }
    if (board[row-'a'][col-'a']!='U')
        return legal;
    for(deltaRow=-1;deltaRow<=1;deltaRow++){
        for(deltaCol=-1;deltaCol<=1;deltaCol++){
            if ((deltaRow!=0)||(deltaCol!=0)){
                if (checkLegalInDirection(board, dimension, row, col, colour, deltaRow, deltaCol) == true){
                    legal = true;
                }
            }
        }
    }
    return legal;
}

bool haveMove(int dimension, char board[26][26], char colour){
    int i,j;
    int deltaRow, deltaCol;
    char row, col;
    bool haveMove = false;
    for(i = 0; i<dimension; i++){
        for(j = 0; j<dimension; j++){
            row = 'a'+i;
            col = 'a'+j;
            if (checkLegal(dimension, board, row, col, colour)==true){
                haveMove = true;
            }
        }
    }
    return haveMove;
}

void finalCompare(int dimension, char board[26][26], char colour, char diffColour){
    int i, j;
    int numColour = 0;
    int numDiffColour = 0;
    for(i = 0; i<dimension; i++){
        for(j = 0; j<dimension; j++){
            if(board[i][j]==colour)
                numColour++;
            else if(board[i][j]==diffColour)
                numDiffColour++;
        }
    }
    if (numColour>numDiffColour)
        printf("%c player wins.",colour);
    else if (numColour<numDiffColour)
        printf("%c player wins.",diffColour);
    else
        printf("Draw!");
}


int score(int dimension, char board[26][26], char colour, int i, int j){
    int score=0;
    char diffColour;
    int numRow, numCol;
    char row, col;
    row = 'a'+i;
    col = 'a'+j;
    if (colour == 'W')
        diffColour ='B';
    if (colour == 'B')
        diffColour = 'W';
    int deltaRow, deltaCol;
    for(deltaRow=-1;deltaRow<=1;deltaRow++){
        for(deltaCol=-1;deltaCol<=1;deltaCol++){
            if((deltaRow!=0)||(deltaCol!=0)){
                if (checkLegalInDirection(board, dimension, row, col, colour, deltaRow, deltaCol)==true){
                    numRow = i;
                    numCol = j;
                    numRow+=deltaRow;
                    numCol+=deltaCol;
                    while(board[numRow][numCol]==diffColour){
                        score++;
                        numRow+=deltaRow;
                        numCol+=deltaCol;
                    }
                }
            }
        }
    }
    return score;
}

void scoreBoard(int dimension, char board[26][26], int copy[26][26], char colour){
    int i,j;
    for(i=0;i<dimension;i++){
        for(j=0;j<dimension;j++){
            copy[i][j]= 0 + score(dimension, board, colour, i, j);
        }
    }
}

void changeBestMove(int dimension, char board[26][26], int copy[26][26], char colour){
    scoreBoard(dimension, board, copy, colour);
    int bestI, bestJ;
    int i, j;
    int count = 0;
    int highScore = 0;
    char row, col;
    for(i=0; i<dimension; i++){
        for (j=0; j<dimension; j++){
            if ((copy[i][j]>0) && (count == 0) && (board[i][j] == 'U')){
                count++;
                bestI = i;
                bestJ = j;
                highScore = copy[i][j];
            }
            else if ((copy[i][j]>highScore) && (board[i][j] == 'U')){
                bestI = i;
                bestJ = j;
                highScore = copy[i][j];
            }
        }
    }
    row = 'a'+bestI;
    col = 'a'+bestJ;
    flipAllAfterLegal(dimension, board, colour, row, col);
    printf("Computer places %c at %c%c.\n", colour, row, col);
    printBoard(board, dimension);
}

int main(void){
    int dimension;
    char board[26][26];
    int i,j;
    int out = 0;
    char row, col;
    char colour, diffColour;
    int deltaRow, deltaCol;
    int copy[26][26];
    printf("Enter the board dimension: ");
    scanf("%d",&dimension);
    
    
    for (i=0;i<dimension;i++){
        for (j=0;j<dimension;j++)
            board[i][j]='U';    //first set all the elements 'U'
    }
    
    
    board[dimension/2-1][dimension/2-1] = 'W';
    board[dimension/2-1][dimension/2] = 'B';
    board[dimension/2][dimension/2-1] = 'B';
    board[dimension/2][dimension/2] = 'W';  //define array in the range of dimension
    
    for(i=0;i<dimension;i++){
        for(j=0;j<dimension;j++){
            copy[i][j]=0;
        }
    }
    
    printf("Computer plays (B/W) : ");
    scanf(" %c",&colour);
    printBoard(board, dimension);   //print the board out
    
    if (colour == 'W')
        diffColour = 'B';
    if (colour == 'B')
        diffColour = 'W';
    
    if (colour == 'W'){
        printf("Enter move for colour %c (RowCol): ", diffColour);
        scanf(" %c %c", &row, &col);
        if (checkLegal(dimension, board, row, col, diffColour) == false){
            printf("Invalid move.\n%c player wins.",colour);
            return EXIT_SUCCESS;
        }
        else{
            board[row-'a'][col-'a']= diffColour;
            flipAllAfterLegal(dimension, board, diffColour, row, col);
            printBoard(board, dimension);
        }
    }
    
    
    
    while (out<1) {
        
        if (haveMove(dimension, board, colour)==true)
            
            changeBestMove(dimension, board, copy, colour);
            
        
        else{
            if (haveMove(dimension, board, diffColour)==true){
                printf("%c player has no valid move.\n",colour);
            }
            else{
                finalCompare(dimension, board, colour, diffColour);
                return EXIT_SUCCESS;
            }
        }
       
        
        
        if (haveMove(dimension, board, diffColour)==true){
            printf("Enter move for colour %c (RowCol): ", diffColour);
            scanf(" %c %c", &row, &col);
            if (checkLegal(dimension, board, row, col, diffColour) == false){
                printf("Invalid move.\n%c player wins.",colour);
                return EXIT_SUCCESS;
            }
            else{
                board[row-'a'][col-'a']= diffColour;
                flipAllAfterLegal(dimension, board, diffColour, row, col);
                printBoard(board, dimension);
            }
        }
        
        
        else{
            if (haveMove(dimension, board, colour)==true){
                printf("%c player has no valid move.\n", diffColour);
            }
            else{
                finalCompare(dimension, board, colour, diffColour);
                return EXIT_SUCCESS;
            }
        }
    }
}

