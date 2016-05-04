/* 
 * File:   main.c
 * Author: weiliche
 *
 * Created on October 28, 2015, 3:32 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

void readInSequence(int length, char sequence[])
{
    char letter;
    int i;
    printf("Enter %d characters (one of AGTC*) as a search sequence: ",length);
    for (i=0; i<length; i++)
    {
        scanf(" %c", &letter);
        sequence[i]=letter;
    }
}

void searching(char sequence[],int length)
{
    int i;
    char DNA[] = {'A', 'G', 'C', 'G', 'G', 'G', 'A', 'C', 'C', 'G', 'T', 'C',
        'C', 'C', 'G', 'A', 'C', 'A', 'T', 'T', 'G', 'A', 'T', 'G',
        'A', 'A', 'G', 'G', 'G', 'T', 'C', 'A', 'T', 'A', 'G', 'A',
        'C', 'C', 'C', 'A', 'A', 'T', 'A', 'C', 'G', 'C', 'C', 'A',
        'C', 'C', 'A', 'C', 'C', 'C', 'C', 'A', 'A', 'G', 'T', 'T',
        'T', 'T', 'C', 'C', 'T', 'G', 'T', 'G', 'T', 'C', 'T', 'T',
        'C', 'C', 'A', 'T', 'T', 'G', 'A', 'G', 'T', 'A', 'G', 'A',
        'T', 'T', 'G', 'A', 'C', 'A', 'C', 'T', 'C', 'C', 'C', 'A',
        'G', 'A', 'T', 'G', '\0'};
    for (i=0;i<=100-length;i++)
    {
        int j;
        bool match = true;
        for (j=0;j<length;j++)
        {
            
            if ((sequence[j]!= DNA[i+j]) &&  (sequence[j]!= '*'))
                match = false;
        }
        if (match)
                printf("Match of search sequence found at element %d\n",i);
    }
}


int main(int argc, const char * argv[])
{
    int length, i;
    printf("Enter length of DNA sequence to match: ");
    scanf("%d",&length);
    char sequence[200];
    while(length>0)
    {
        readInSequence(length,sequence);
        for (i=0;i<length;i++)
        {
            if ((sequence[i]!='A')&&(sequence[i]!='G')&&(sequence[i]!='C')&&(sequence[i]!='T')&&(sequence[i]!='*'))
            {
                printf("Erroneous character input '%c' exiting\n",sequence[i]);
                printf("Goodbye");
                return 0;
            }
        }
        searching(sequence,length);
        printf("Enter length of DNA sequence to match: ");
        scanf("%d",&length);
    }
    printf("Goodbye");
    return 0;
}
   


