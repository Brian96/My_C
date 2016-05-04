/* 
 * File:   main.c
 * Author: weiliche
 *
 * Created on September 22, 2015, 2:23 PM
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * 
 */
int main(int argc, char** argv) {
    double age,doctorEstimate,likelihood,BNTP;
    printf("Enter patient age: ");
    scanf("%lf",&age);
    printf("Enter doctor %% likelihood guess of heart failure: ");
    scanf("%lf",&doctorEstimate);
    printf("Enter patient BNPT value (between 0 and 1000 pg/ml): ");
    scanf("%lf",&BNTP);
    likelihood=(doctorEstimate/1.5)+(age/10)+(BNTP/125.0)*20;//calculation to get the answer
    printf("Computed likelihood of heart failure is %.1lf%%",likelihood);
    return (EXIT_SUCCESS);
}

