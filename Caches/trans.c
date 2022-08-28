/*
 * CSE 351 Lab 4 (Caches and Cache-Friendly Code)
 * Part 2 - Optimizing Matrix Transpose
 *
 * Name(s): Edison Leung 
 * NetID(s): 2136014
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[M][N], int B[N][M]);
 * and compute B = A^T.
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1 KiB direct mapped cache with a block size of 32 bytes.
 */

#include <stdio.h>
#include "support/cachelab.h"

int is_transpose(int M, int N, int A[M][N], int B[N][M]);


/*
 * transpose_submit - This is the transpose function that you will be graded
 *     on. Do not change the description string "Transpose submission", as the
 *     driver searches for that string to identify the transpose function to be
 *     graded.
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[M][N], int B[N][M]) {
    
    int i,j,k;
    if (M == 32) {
       for (i = 0; i < M; i+=8) {
          for (j = 0; j < N; j+=8) {
	     for (k = 0; k < 8; k++) {
                int temp[8] = {A[i+k][j],
	    	     	      A[i+k][j+1],
			      A[i+k][j+2],
			      A[i+k][j+3],
			      A[i+k][j+4],
			      A[i+k][j+5],
			      A[i+k][j+6],
			      A[i+k][j+7]
			     };
	        B[j][i+k] = temp[0];
	        B[j+1][i+k] = temp[1];
	        B[j+2][i+k] = temp[2];
	        B[j+3][i+k] = temp[3];
	        B[j+4][i+k] = temp[4];
       	        B[j+5][i+k] = temp[5];
	        B[j+6][i+k] = temp[6];
	        B[j+7][i+k] = temp[7];
	    }
          }
       }
    } else if (M == 64){
	     for (i = 0; i < 64; i+=4) {
	     	for (j = 0; j < 64; j+=4) {
		   for (k = 0; k < 4; k++) {
		   	int temp[4] = {A[i+k][j],
				      A[i+k][j+1],
				      A[i+k][j+2],
				      A[i+k][j+3]};
		 	B[j][i+k] = temp[0];
			B[j+1][i+k] = temp[1];
			B[j+2][i+k] = temp[2];
			B[j+3][i+k] = temp[3];
		   }
		}
	     }
	  
    }
}


// You can define additional transpose functions below. We've defined a simple
// one below to help you get started.

/*
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[M][N], int B[N][M]) {
    int i, j, tmp;

    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }

}


/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions() {
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc);

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc);

}


/*
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[M][N], int B[N][M]) {
    int i, j;

    for (i = 0; i < M; i++) {
        for (j = 0; j < N; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}
