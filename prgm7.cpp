#include<stdio.h>
#include<omp.h>
#include<stdlib.h>

/* Main Program */
int main()
{
    float *array_A, sum, *checkarray, serialsum;
    int arraysize, i, k, Noofthreads;

    printf("Enter the size of the array \n");
    scanf("%d", &arraysize);

    if (arraysize <= 0) {
        printf("Positive Number Required\n");
        exit(1);
    }

    /* Dynamic Memory Allocation */
    array_A = (float *) malloc(sizeof(float) * arraysize);
    checkarray = (float *) malloc(sizeof(float) * arraysize);
    
    for (i = 0; i < arraysize; i++) {
        array_A[i] = i + 5;
        checkarray[i] = array_A[i];
    }

    printf("\nThe input array is \n");
    for (i = 0; i < arraysize; i++)
        printf("%f \t", array_A[i]);
    sum = 0.0;

    /* OpenMP Parallel For With Reduction Clause */
    #pragma omp parallel for reduction(+ : sum)
        for (i = 0; i < arraysize; i++)
            sum = sum + array_A[i];

    /* Serial Calculation */
    serialsum = 0.0;

    for (i = 0; i < arraysize; i++)
        serialsum = serialsum + array_A[i];
    
    /* Output Checking */
    if (serialsum != sum) {
        printf("\nThe calculation of array sum is different \n");
        exit(1);
    } else
        printf("\nThe calculation of array sum is same\n");

    /* Freeing Memory Which Was Allocated */
    free(checkarray);
    free(array_A);

    printf("The value of array sum using threads is %f\n", sum);
    printf("\nThe serial calculation of array is %f\n", serialsum);

    return 0;
}
