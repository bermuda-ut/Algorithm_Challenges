/*=============================================================================
#     FileName: quicksort-nemesis.c
#         Desc: Algorithm that generates a list that forces quick sort to
#               follow O(n^2), the worst case scenario, given that the
#               selection of pivot method is n/2
#               For a quick sort algorithm to overcome this issue, the algorithm
#               must choose the pivot randomly.
#       Author: Max Lee (Ho Suk Lee)
#        Email: hoso1312@gmail.com
#     HomePage: http://imnotbermuda.com
#      Version: 0.0.1
#   LastChange: 2015-08-31 00:17:03
#      History: 0.0.1 - Initial version
#
# Instructions: quicksort-nemesis [r/n] [TEST_SIZE] [TEST_FREQ]
#               All command line arguments are optional and defaults to
#               n, 10000, 10
=============================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

/* Data type in the array can be changed here */

typedef int arrtype;

/* Treat as constant, these values may change only once at the start */
int TEST_SIZE = 10000;
int TEST_FREQ = 10;

int cmp(arrtype* a, arrtype* b);
arrtype choose_pivot(arrtype array[], int size, int israndom);
void partition(arrtype array[], int size, arrtype* pivot, int* first_eq,
        int* first_gr);
void qksrtneme(arrtype array[], int n);
void valswap(arrtype* a, arrtype* b);
void quicksort(arrtype array[], int size, int israndom);
void fillrandom(arrtype array[], int size, int limit);
void copyarray(arrtype source[], arrtype dest[]);
void test(int israndom, arrtype array[]);
void nemesistest(int israndom, arrtype array[]);

int
main(int argc, char **argv) {
    /* Quick test with random values to show that n/2 method
     * results are almost equal to random method if the array
     * is random */
    if(argc >= 3) {
        TEST_SIZE = atoi(argv[2]);
    }
    if(argc == 4) {
        TEST_FREQ = atoi(argv[3]);
    }
    arrtype arrayone[TEST_SIZE], arraynemesis[TEST_SIZE];

    if (argv[1] && *argv[1] == 'r') {
        /* 'r' arguement = random pivot */
        test(1, arrayone);
    } else {
        /* No or any other arguement = n/2 pivot */
        test(0, arrayone);
    }

    qksrtneme(arraynemesis, TEST_SIZE);
    printf("[WARNING] Quicksort nemesis has arrived.\n");


    printf("Demonstration:\n");
    printf("1 2 4 3 0\n1 2 3 0 4\n1 2 0 3 4\n1 0 2 3 4\n0 1 2 3 4\n\n");

    if (argv[1] && *argv[1] == 'r') {
        /* 'r' arguement = random pivot */
        nemesistest(1, arraynemesis);
    } else {
        /* No or any other arguement = n/2 pivot */
        nemesistest(0, arraynemesis);
    }
    return 0;
}

/*===================
# Nemesis Algorithm 
===================*/

void 
qksrtneme(arrtype array[], int size) {
    /* Assumes array is big enough
     * " I am your nightmare " */
    arrtype i=0;
    int idx=0, secondtime=0;

    /* Make the pivot the greatest value */
    while(i<size) {
        if(secondtime) {
            array[size-1-idx] = i;
            idx++;
            secondtime = 0;
        } else {
            array[idx] = i;
            secondtime = 1;
        }
        i++;
    }

    valswap(&array[0], &array[size-1]);
}

/*=======================
# Quicksorting Algorithm
# Testing Purpose
=======================*/

void
nemesistest(int israndom, arrtype array[]) {
    clock_t start, end;
    double timespent;
    int i;
    arrtype temparray[TEST_SIZE];

    /* Timer starts */
    start = clock();

    if(israndom) {
        printf("random pivot quicksort of nemesis array\n");
    } else {
        printf("n/2 pivot quicksort of nemesis array\n");
    }
    /* Test sorting. Time is slightly affected by copy array */
    for(i=0; i<TEST_FREQ; i++) {
        copyarray(array, temparray);
        quicksort(temparray, TEST_SIZE, israndom);
    }

    end = clock();
    /* Timer ends */

    timespent = ((double) end - start) / CLOCKS_PER_SEC;
    printf("Nemesis array with %d values, %d time(s).\n",
            TEST_SIZE, TEST_FREQ);
    printf("Execution time: %.4fs\n", timespent);
    printf("\n");
}

void
test(int israndom, arrtype array[]) {
    /* Using array from main in case of manual testing */
    clock_t start, end;
    double timespent;
    int i;

    /* Timer starts */
    start = clock();
    if(israndom) {
        printf("random pivot quicksort of random array\n");
    } else {
        printf("n/2 pivot quicksort of random array\n");
    }
    /* Test sorting. Time is slightly affected by random fills */
    for(i=0; i<TEST_FREQ; i++) {
        fillrandom(array, TEST_SIZE, 1000);
        quicksort(array, TEST_SIZE, israndom);
    }

    end = clock();
    /* Timer ends */

    timespent = ((double) end - start) / CLOCKS_PER_SEC;
    printf("Sorted arrays with %d random values, %d times.\n",
            TEST_SIZE, TEST_FREQ);
    printf("Execution time: %.4fs\n", timespent);
    printf("\n");
}

void
quicksort(arrtype array[], int size, int israndom) {
    arrtype pivot;
    int first_eq, first_gr;

    if(size <= 1) {
        /* Base case */
        return;
    }

    pivot = choose_pivot(array, size, israndom);
    partition(array, size, &pivot, &first_eq, &first_gr);
    /* Partition into less|equal|greater then sort less&greater */
    quicksort(array, first_eq, israndom);
    quicksort(array+first_gr, size-first_gr, israndom);
}

void
partition(arrtype array[], int size, arrtype* pivot, int* first_eq,
        int* first_gr) {
    int next = 0, fe = 0, fg = size, outcome;

    /* Partition into less|equal|greater */
    while(next < fg) {
        /* Self-explanatory */
        if((outcome = cmp(array+next, pivot)) < 0) {
            valswap(array+next, array+fe);
            fe++;
            next++;
        } else if(outcome > 0) {
            fg--;
            valswap(array+next, array+fg);
        } else {
            next++;
        }
    }

    *first_eq = fe;
    *first_gr = fg;
    return;
}

int
cmp(arrtype* a, arrtype* b) {
    /* Negative if less, positive if more, 0 if equal */
    if(*a < *b) {
        return -1;
    } else if(*a > *b) {
        return 1;
    }
    return 0;
}
void
valswap(arrtype* a, arrtype* b) {
    arrtype temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

arrtype
choose_pivot(arrtype array[], int size, int israndom) {
    if(israndom) {
        int piv = (int) rand() / (RAND_MAX / size + 2);
        /*
        printf("pivot = %d\n", piv);
        */
        return array[piv];
    }
        /*
        printf("pivot = %d\n", size/2);
        */
    return array[size/2];
}

void
fillrandom(arrtype array[], int size, int limit) {
    /* Assumes limit is big enough */
    int i;
    for(i=0; i<size; i++) {
        array[i] = rand() % limit;
    }
}

void
copyarray(arrtype source[], arrtype dest[]) {
    while((*dest++ = *source++));
}

