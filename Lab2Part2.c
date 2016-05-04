/* 
 * File:   main.c
 * Author: weiliche
 *
 * Created on September 22, 2015, 2:40 PM
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * 
 */
int main(int argc, char** argv) {
    int basedTenNumber,binaryNumber,B0,B1,B2,B3;
    printf("Enter 4-bit binary number: ");//input number in a binary
    scanf("%d",&binaryNumber);//receive the number in a binary form
    B3=binaryNumber/1000;
    B2=(binaryNumber-1000*B3)/100;
    B1=(binaryNumber-1000*B3-100*B2)/10;
    B0=binaryNumber-1000*B3-100*B2-10*B1;//get each digits in binary number
    basedTenNumber=B0*1+B1*2+B2*4+B3*8;//get the number in base 10
    printf("%d in base 2 is %d in base 10",binaryNumber,basedTenNumber);
    return (EXIT_SUCCESS);
}

