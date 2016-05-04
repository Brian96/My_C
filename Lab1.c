/* 
 * File:   main.c
 * Author: weiliche
 *
 * Created on September 22, 2015, 2:58 PM
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * 
 */
int main(int argc, char** argv) {
    int firstNumber,secondNumber;
    printf("Enter First Number: ");
    scanf("%d",&firstNumber);
    printf("Enter Second Number: ");
    scanf("%d",&secondNumber);
    int sum,difference,squareOfNumber1,squareOfNumber2,division;
    sum=firstNumber+secondNumber;
    difference=firstNumber-secondNumber;
    squareOfNumber1=firstNumber*firstNumber;
    squareOfNumber2=secondNumber*secondNumber;
    division=secondNumber/firstNumber;
    printf("Sum: %d\n",sum);
    printf("Difference: %d\n",difference);
    printf("Square of Number 1: %d\n",squareOfNumber1);
    printf("Square of Number 2: %d\n",squareOfNumber2);
    printf("Division: %d",division);
    return (EXIT_SUCCESS);
}

