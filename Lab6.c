/* 
 * File:   Lab6.c
 * Author: weiliche
 *
 * Created on November 2, 2015, 6:14 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/*
 * 
 */
void printBoard(char board[26][26], int n);
void boardConfiguration(char board[26][26]);
void findAvailableMoves(int dimension, char board[26][26], char colour);
void flip(int dimension, char board[26][26], char colour, int row, int col, int deltaRow, int deltaCol);
void checkValid(int dimension, char board[26][26]);
bool positionInBounds(int N, char row, char col);
bool checkLegalInDirection(char board[26][26], int N, char row, char col, char colour, int deltaRow, int deltaCol);
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

void boardConfiguration(char board[26][26]){
    printf("Enter board configuration:\n");
    char letter;
    int n;
    char colour, col, row;
    do{
        scanf(" %c",&colour);
        scanf(" %c",&row);
        scanf(" %c",&col);
        board[(row-'a')][(col-'a')]=colour; //change the board according to user input 
    }while((colour!='!')&&(col!='!')&&(row!='!'));  
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

void findAvailableMoves(int dimension, char board[26][26], char colour){
    int i, j;
    for (i=0;i<dimension;i++){
        for (j=0;j<dimension;j++){
            char row = 'a'+i;
            char col = 'a'+j;
            if (positionInBounds(dimension,row,col)==true && board[i][j]=='U'){ //get the boundary inside
                bool legal = false;
                int deltaRow, deltaCol;
                for(deltaRow=-1;deltaRow<=1;deltaRow++){
                    for(deltaCol=-1;deltaCol<=1;deltaCol++){
                        if ((deltaRow!=0)||(deltaCol!=0)){  //all eight directions except from 0 0
                            if(checkLegalInDirection(board,dimension,row,col,colour,deltaRow,deltaCol)==true)
                                legal = true;   //true means there are at least one direction is legal move that the move can be put here
                        }
                    }
                }
                if(legal == true)
                    printf("%c%c\n",row,col);   //if at least one move is available print the move out
            }
        }
    }
}

void flip(int dimension, char board[26][26], char colour, int row, int col, int deltaRow, int deltaCol){
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

void checkValid(int dimension, char board[26][26]){
    printf("Enter a move:\n");
    char colour, row, col;
    bool legal = false;
    scanf(" %c %c %c",&colour,&row,&col);
    int deltaRow, deltaCol;
    for(deltaRow=-1;deltaRow<=1;deltaRow++){
        for(deltaCol=-1;deltaCol<=1;deltaCol++){
            if ((deltaRow!=0)||(deltaCol!=0)){
                if (checkLegalInDirection(board, dimension, row, col, colour, deltaRow, deltaCol) == true){
                    flip(dimension, board, colour, row, col, deltaRow, deltaCol);
                    legal = true;
                }   //flip for each move at each direction that is true
            }
        }
    }
    if (legal == false){
        printf("Invalid move.\n");
        printBoard(board,dimension);  
    }  
    else{
        printf("Valid move.\n");
        printBoard(board,dimension);
    }
}


int main(void){
    int dimension;
    char board[26][26];
    int i,j;
    printf("Enter the board dimension: ");
    scanf("%d",&dimension);
    for (i=0;i<dimension;i++)
    {
        for (j=0;j<dimension;j++)
            board[i][j]='U';    //first set all the elements 'U'
    }
    board[dimension/2-1][dimension/2-1] = 'W';
    board[dimension/2-1][dimension/2] = 'B';
    board[dimension/2][dimension/2-1] = 'B';
    board[dimension/2][dimension/2] = 'W';  //define array in the range of dimension
    
    printBoard(board, dimension);   //print the board out
    
    boardConfiguration(board);  //do some changes to the board with no color flip
    
    printBoard(board, dimension);   //print the changed board out
    
    printf("Available moves for W:\n");
    
    findAvailableMoves(dimension, board, 'W');  //find and print available moves for W
    
    printf("Available moves for B: \n");
    
    findAvailableMoves(dimension, board, 'B');  //find and print available moves for B
    
    checkValid(dimension, board);   //ask for a move and do the following operations
    
    return EXIT_SUCCESS;
}

