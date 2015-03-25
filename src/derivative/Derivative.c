// The compilation command used is given below
// gcc Q3.c nrutil.c DFRIDR.c -lm -o Q3

#include <stdio.h>
#include <math.h>
#include "nr.h"

#define LIM1 20.0
#define a -5.0
#define b 5.0
#define pre 100.0 // This defines the pre
/* This file calculates the func at given points, makes a 
 * plot. It also calculates the maximum and minimum of the func
 * at given points and its first and second numerical derivative.
*/
float func(float x)
{
    return exp(x / 2) / pow(x, 2);
}

int main(void)
{
    FILE *fp = fopen("Q3data.dat", "w+"), *fp2 = fopen("Q3results.dat", "w+");
    int i; // Declaring our loop variable
    float x, y, min, max, err, nd1, nd2;
    // Define the initial value of the func to be the minimum
    min = func(0); 
    for(i = 0; x < LIM1 ; i++)
    {   
        x = i / pre; // There is a singularity at x = 0 
        y = func(x);
        if(y < min)
            min = y;
        fprintf(fp, "%f \t %f \n", x, y);
    }
    fprintf(fp, "\n\n");
    max = 0;
    for(i = 0, x = a; x < b; i++)
    {   
        x = a + i / pre;
        y = func(x);
        nd1 = dfridr(func, x, 0.1, &err); 
        //nd2 = dfridr((*func), x, 0.1, &err);
        fprintf(fp, "%f \t %f \t %f \t %f \n", x, y, nd1);
        if(y > max)
            max = y;
    }

    fprintf(fp2, "The minimum value of f(x) is %f when x is between 0 and 20. \n", min);
    fprintf(fp2, "The maximum value of f(x) is %f when x is between -5 and 5. \n", max);
    fclose(fp);
    fclose(fp2);
    return 0;
}
