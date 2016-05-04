/* 
 * File:   Lab4.c
 * Author: weiliche
 *
 * Created on October 21, 2015, 6:15 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double gaussFunc (double x, double spread)
{
    double output;
    output = exp(-x*x/spread);
    return output;
}

int main(int argc, char** argv) {
    double spread, minLim, maxLim, integral, width, midPoint;
    int num;
    printf("Enter the spread value (must be >0): ");
    scanf("%lf", &spread);
    while (spread <= 0)
    {
        printf("Enter the spread value (must be >0): ");
        scanf("%lf", &spread);
    }
    printf("Please enter the number of rectangles (n): ");
    scanf("%d", &num);
    while (num >= 1)
    {
        printf("Enter the interval of integration (a b): ");
        scanf("%lf %lf", &minLim, &maxLim);
        while (minLim > maxLim)
        {
            printf("Invalid interval!\n");
            printf("Enter the interval of integration (a b): ");
            scanf("%lf %lf",&minLim,&maxLim);
        }
        width = (maxLim-minLim)/num;
        midPoint=maxLim+width/2;
        integral = 0; 
        while (midPoint>minLim+width/2)
        {
            midPoint=midPoint-width;
            integral=integral+width*gaussFunc(midPoint,spread);
        }
        printf("Integral of Gaussian with spread %.3lf on [%.3lf, %.3lf] with n = %d is: %.3lf\n",spread,minLim,maxLim,num,integral);
        printf("Please enter the number of rectangles (n): ");
        scanf("%d", &num);
    }
    printf("Exiting.");
    return (EXIT_SUCCESS);
}

