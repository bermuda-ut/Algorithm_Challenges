/*=============================================================================
#     FileName: permutate.c
#         Desc: Prints permutation combination from 1 until specified number
#       Author: Max Lee (Ho Suk Lee)
#        Email: hoso1312@gmail.com
#     HomePage: http://imnotbermuda.com
#      Version: 1.0.1
#   LastChange: 2015-11-05 21:51:29
=============================================================================*/
#include <stdio.h>
#include <stdlib.h>

void
printarray(int *array, int size) {
    /* Print all the elements in the array then new line */
    int i;
    for(i=0; i<size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void
intswap(int *a, int *b) {
    int c = *a;
    *a = *b;
    *b = c;
}

void
rec_per(int lead, int *array, int size) {
    /* Logic   : if divided into small steps, its fundamentally swapping places
     *           for two numbers.
     * Pattern : There is a 'leading' number and it swaps place with each
     *           numbers after the leading number
     * Recursively repeat the pattern for each number */
    int i;

    if(size == lead) {
        /* Reached the end of the list, nothing more to swap, print. */
        printarray(array, size);
        return;
    }

    for(i=lead; i<size; i++) {
        /* Follow the pattern of swapping with lead
         * little trick : swaps itself with itself first! */
        intswap(array+lead, array+i);
        rec_per(lead+1, array, size);

        /* Restore back for next lead term */
        intswap(array+lead, array+i);
    }
}

void
permute(int n) {
    /* Creates permutation pattern from 1 to given number */
    int i, list[n];

    /* Generate list */
    for(i=0; i<n; i++) {
        list[i] = i+1;
    }

    /* Recursively print out patterns */
    rec_per(0, list, n);
}

int
main(int argc, char **argv) {
    if(argc==2) {
        permute(atoi(argv[1]));
    } else {
        printf("Invalid argument.\nUsage: permutate [number]\n");
    }
    return 0;
}
