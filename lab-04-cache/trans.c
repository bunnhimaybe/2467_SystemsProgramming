/* 
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 *
 * Melita Nelson: mbnelso1@uno.edu
 * Nhi Pham
 */ 
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N]) {
    int i, j, k, l, temp, diagonal;

if (M == 64) {
        // Optimized for 64x64 matrices using 4x4 blocking
        for (j = 0; j < 64; j += 4) {  // Outer loop iterates over column blocks
            for (i = 0; i < 64; i += 4) {  // Inner loop iterates over row blocks
                for (k = i; k < i + 4 && k < 64; k++) {  // Rows within a block
                    for (l = j; l < j + 4 && l < 64; l++) {  // Columns within a block
                        if (k != l) {
                            B[l][k] = A[k][l];  // Transpose non-diagonal elements
                        } else {
                            temp = A[k][l];  // Temporarily store diagonal element
                            diagonal = k;
                        }
                    }
                    if (i == j) {
                        B[diagonal][diagonal] = temp;  // Place diagonal element
                    }
                }
            }
        }
    } else if (M == 32) {
        // Optimized for 32x32 matrices using 8x8 blocking
        for (i = 0; i < 32; i += 8) {  // Outer loop iterates over row blocks
            for (j = 0; j < 32; j += 8) {  // Inner loop iterates over column blocks
                for (k = i; k < i + 8 && k < 32; k++) {  // Rows within a block
                    for (l = j; l < j + 8 && l < 32; l++) {  // Columns within a block
                        if (k != l) {
                            B[l][k] = A[k][l];  // Transpose non-diagonal elements
                        } else {
                            temp = A[k][l];  // Temporarily store diagonal element
                            diagonal = k;
                        }
                    }
                    if (i == j) {
                        B[diagonal][diagonal] = temp;  // Place diagonal element
                    }
                }
            }
        }
    } else { 
        // For rectangular matrices, using a flexible 16x16 blocking strategy
        for (i = 0; i < N; i += 16) {  // Outer loop iterates over row blocks
            for (j = 0; j < M; j += 16) {  // Inner loop iterates over column blocks
                for (k = i; k < i + 16 && k < N; k++) {  // Rows within a block
                    for (l = j; l < j + 16 && l < M; l++) {  // Columns within a block
                        B[l][k] = A[k][l];  // Transpose element
                    }
                }
            }
        }
    }
}



/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */ 

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
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
void registerFunctions()
{
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
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}
