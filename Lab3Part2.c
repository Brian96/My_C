/* 
 * File:   main.c
 * Author: weiliche
 *
 * Created on October 1, 2015, 10:39 AM
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * 
 */
int main(int argc, char** argv) {
    int seed, inputNumber, pickedNumber;
    printf("Enter seed: ");
    scanf("%d", &seed);
    srand(seed);
    printf("Guess a number from 1 to 7 (<=0 to quit): ");
    scanf("%d", &inputNumber);
    while (inputNumber >= 1)//start the loop
    {
        if (inputNumber > 7)
            printf("Number too high, guess again!\n");
        else
        {
            pickedNumber=rand()%7+1;//random number picked between 1 and 7
            printf("Number picked: %d\n", pickedNumber);
            if (inputNumber == pickedNumber)
                printf("Good guess!\n");
            else
                printf("Sorry, try again!\n");
        }  
        printf("Guess a number from 1 to 7 (<=0 to quit): ");
        scanf("%d", &inputNumber);
    }
    printf("Goodbye");
    return (EXIT_SUCCESS);
}

