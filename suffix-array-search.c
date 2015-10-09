/*=============================================================================
#     FileName: suffix-array-search-search.c
#         Desc: suffix array search for query in text
#       Author: Max Lee
#        Email: hoso1312@gmail.com
#     HomePage: http://imnotbermuda.com
#      Version: 0.0.1
#   LastChange: 2015-09-12 21:35:21
=============================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 1

void int_swap(int *a, int *b);

void str_qpartition(int array[], char val[], int size, char *pivot,
        int *fequal, int *fgreat, int depth);
int char_cmp(char *a, char *b);
void str_qsort(int array[], char str[], int size, int depth);
int binary_count_idx(int idx[], char *query, char *str, int qlen, int llen);

int idx_search_count(char *query, char *string, int qlen, int llen,
                    int* idxlist);

int
main(int argc, char **argv) {
    if(argc < 3) {
        printf("Insufficient arguments\n");
        printf("Usage: %s QUERY STRING\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int value, qlen=strlen(argv[1]), llen=strlen(argv[2]), idxlist[llen], i;

    for(i=0; i<llen; i++) {
        idxlist[i] = i;
    }

    /* Generate suffix array */
    str_qsort(idxlist, argv[2], llen, 0);
    /* Find from array. In reality, want to search multiple times to make
     * the algorithm shine */
    value = idx_search_count(argv[1], argv[2], qlen, llen, idxlist);
    printf("%d found.\n", value);

    return 0;
}

int
idx_search_count(char *query, char *str, int qlen, int llen, int* idxlist) {
    /* Rather redundant function
     * Initial idea was that binary count idx was recursive and needed a
     * calling function to print debug but binary_count_idx turned out to
     * be easier if iterative. */
#if DEBUG
    int i;
    for(i=0; i<llen; i++) {
        printf("%3d", i);
    }
    printf("\n");

    for(i=0; i<llen; i++) {
        printf("%3c", str[idxlist[i]]);
    }
    printf("\n");

    for(i=0; i<llen; i++) {
        printf("%3d", idxlist[i]);
    }
    printf("\n");
    printf("\n");

    for(i=0; i<llen; i++) {
        printf("%3d%3d %s\n", i, idxlist[i], str+idxlist[i]);
    }
    printf("\n");
#endif
    
    return binary_count_idx(idxlist, query, str, qlen, llen);
}

int
binary_count_idx(int idx[], char *query, char *str, int qlen, int llen) {
    /* Binary search with depth + start&end point to determine the position
     * of the string */
    int lo, hi, depth=0, mid, start=0, end=llen;

    while(depth < qlen) {
        /* inclusive */
        lo = start;
        hi = end;

        while(lo<hi) {
            /* search for starting idx */
            mid = (lo+hi)/2;
            if(char_cmp(str+idx[mid]+depth, query+depth) < 0) {
                /*strictly less*/
                lo = mid+1;
            } else {
                hi = mid;
            }
        }

        start = lo;
        hi = end;

        while(lo<hi) {
            /* search for ending idx */
            mid = (lo+hi)/2;
            if(char_cmp(str+idx[mid]+depth, query+depth) > 0) {
                /*strictly more*/
                hi = mid;
            } else {
                lo = mid+1;
            }
        }
        end = hi;

        depth++;
    }

#if DEBUG
    printf("start %d, end%d\n", start, end);
#endif
    return end-start;
}

void
str_qpartition(int array[], char val[], int size, char *pivot, int *fequal,
                int *fgreat, int depth) {
    /* Partition into < | = | > */
    int nxt=0, fe=0, fg=size, result;

    while(nxt < fg) {
        if((result = char_cmp(val+array[nxt]+depth, pivot+depth)) < 0) {
            int_swap(array+fe, array+nxt);
            fe++;
            nxt++;
        } else if(result > 0) {
            fg--;
            int_swap(array+nxt, array+fg); 
        } else {
            nxt++;
        }
    }

    *fequal = fe;
    *fgreat = fg;
}

void
str_qsort(int array[], char str[], int size, int depth) {
    /* Recursively quicksort the list */
    int fgreat, fequal;
    char *pivot;
    if(size <= 1) {
        return;
    }

    pivot = str+array[rand()%size];
    /* random for average case and protection against worst case scenarios */

    str_qpartition(array, str, size, pivot, &fequal, &fgreat, depth);
    /* Guranteed all unique string therefore no guard to end loop */
    str_qsort(array, str, fequal, depth);
    str_qsort(array+fequal, str, fgreat-fequal, depth+1);
    str_qsort(array+fgreat, str, size-fgreat, depth);
}

int
char_cmp(char *a, char *b) {
    /* Returns negative if a is less, positive if a is greater, 0 if equal */
    if(*a < *b) {
        return -1;
    } else if(*a > *b) {
        return 1;
    } else {
        return 0;
    }
}

void
int_swap(int *a, int *b) {
    /* swap integer values */
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

