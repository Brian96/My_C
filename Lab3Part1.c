/* 
 * File:   main.c
 * Author: weiliche
 *
 * Created on October 2, 2015, 11:28 AM
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * 
 */
int main(int argc, char** argv) {
    double firstNumber, secondNumber;
    char calCom;//define names of two numbers and the calculation command
    printf("Enter first number: ");
    scanf("%lf", &firstNumber);
    printf("Enter second number: ");
    scanf("%lf", &secondNumber);
    printf("Enter calculation command (one of a, s, m, or d): ");
    scanf(" %c", &calCom);
    if (calCom == 'a')
        printf("Sum of %.2lf and %.2lf is %.2lf", firstNumber, secondNumber, firstNumber+secondNumber);
    else if (calCom == 's')
        printf("Difference of %.2lf from %.2lf is %.2lf", firstNumber, secondNumber, firstNumber-secondNumber);
    else if (calCom == 'm')
        printf("Product of %.2lf and %.2lf is %.2lf", firstNumber, secondNumber, firstNumber*secondNumber);
    else if (calCom == 'd')
    {
        if (secondNumber != 0)
            printf("Division of %.2lf by %.2lf is %.2lf", firstNumber, secondNumber, firstNumber/secondNumber);
        else
            printf("Error, trying to divide by zero");
    }
    else
        printf("Error, unknown calculation command given");
    return (EXIT_SUCCESS);
}

