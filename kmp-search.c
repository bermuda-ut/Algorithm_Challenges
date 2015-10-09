/*=============================================================================
#     FileName: kmp-search.c
#         Desc: KMP search for multiple occurences in text
#       Author: Max Lee
#        Email: hoso1312@gmail.com
#     HomePage: http://imnotbermuda.com
#      Version: 0.0.1
#   LastChange: 2015-09-12 21:35:21
=============================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <math.h>

#define DEBUG 1

void KMP_gen_F(char* query, int qlen, int* F);
int KMP_search(char* query, char* str, int qlen, int strlen);

int
main(int argc, char **argv) {
    if(argc < 3) {
        printf("Insufficient arguments\n");
        printf("Usage: %s QUERY STRING\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int value, qlen=strlen(argv[1]), llen=strlen(argv[2]);

    value = KMP_search(argv[1], argv[2], qlen, llen);
#if DEBUG
    printf("STRING: %s\n", argv[2]);
#endif
    printf("%d found.\n", value);

    return 0;
}

void
KMP_gen_F(char* query, int qlen, int* F) {
    /* Generate failure array for query into F */
    int posQ=2, cnd=0;
    F[0] = -1;
    F[1] = 0;

    while(posQ < qlen) {
        if(query[posQ-1] == query[cnd]) {
            cnd++;
            F[posQ] = cnd;
            posQ++;
        } else if(cnd > 0) {
            cnd = F[cnd];
        } else {
            F[posQ] = 0;
            posQ++;
        }
    }
}

int
KMP_search(char* query, char* str, int qlen, int strlen) {
    int posL=0, posQ=0, freq=0, F[qlen];

    /* Generate failure array here for demonstration purpose.
     * Practically, you want to generate F outside this fuction then feed it
     * into this function and search over multiple texts to make the
     * efficiency shine. */
    KMP_gen_F(query, qlen, F);

#if DEBUG
    int i;
    for(i=0; i<qlen; i++) {
        printf("%4c", query[i]);
    }
    printf("\n");
    for(i=0; i<qlen; i++) {
        printf("%4d", F[i]);
    }
    printf("\n");
#endif

    /* Generic KMP algorithm with slight change to find multiple matches */
    while(posL <= strlen-qlen) {
        if(str[posL + posQ] == query[posQ]) {
            posQ++;
            if(posQ == qlen) {
                freq++;
                /* Pretend havn't found and continue on for multiple match */
                posL = posL + posQ - 1 - F[posQ-1];
                /* posQ-1 since it was found and increased previously */
                posQ = 0;
            }
        } else {
            posL = posL + posQ - F[posQ];
            posQ = 0;
        }
    }

    return freq;
}

