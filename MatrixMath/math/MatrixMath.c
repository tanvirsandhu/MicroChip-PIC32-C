/* 
 * File:   MatrixMath.c
 * Author: Tanvir Sandhu (taksandh@ucsc.edu)
 *
 * Created on January 25, 2021, 1:39 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "MatrixMath.h"
#include "BOARD.h"
#include <math.h>

/*
 * 
 */
float MatrixDeterminant2x2(float mat[2][2]);
int MatrixCheck(float mat1[2][2], float mat2[2][2]);

//Matrix Print Function
void MatrixPrint(float mat[3][3])
{   
    printf("__________________________________\n");
    for(int i = 0; i < 3; i++) {
        printf("|");
        for(int j = 0; j < 3; j++) {
            printf(" %lf |", mat[i][j]);
        }
    printf("\n");    
    printf("----------------------------------\n");
    } 
} 

//Matrix Equals Function
int MatrixEquals(float mat1[3][3], float mat2[3][3])
{   
    float z = 0;
    //nested for loops iterate through all values of i and j (row and column)
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            //checks if the number at i, j is the same for both matrices within .0001
                //if it is, then the loop continues to check every value
            z = mat1[i][j] - mat2[i][j]; 
            z = fabs(z);
            if (z < FP_DELTA) {
                continue;   
            }
            //if even one spot is not equal, the function will return 0, or false.
            else {
                return 0;
            }
        }
    }
    //if it all works successfully, function will return 1, or true
    return 1;
}

void MatrixAdd(float mat1[3][3], float mat2[3][3], float result[3][3]) 
{
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            //the result matrix at i,j is the result of mat1 + mat2 at i,j
            result[i][j] = mat1[i][j] + mat2[i][j];
        }
    }
}

void MatrixMultiply(float mat1[3][3], float mat2[3][3], float result[3][3])
{
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            //because we're iterating through each matrix differently, a third
                //loop is required to go rows in one and columns in the other
            for (int k = 0; k < 3; k++) {
                result[i][j] += mat1[i][k] * mat2[k][j];
            }    
        }
    }
}

void MatrixScalarAdd(float x, float mat[3][3], float result[3][3])
{
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            //just add the scalar to each matrix entry
            result[i][j] = mat[i][j] + x;
        }
    }
}

void MatrixScalarMultiply(float x, float mat[3][3], float result[3][3])
{
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            //just multiplying the scalar to each matrix entry
            result[i][j] = mat[i][j] * x;
        }
    }
}

float MatrixTrace(float mat[3][3])
{   
    int x = 0;
    for (int i = 0; i < 3; i++) {
        //only one loop required because the indices we are adding having the same
            //row and column number so one variable can be used.
        x += mat[i][i];
    } 
    return x;
}

void MatrixTranspose(float mat[3][3], float result[3][3])
{
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            //simply switch the i and j to switch the row and column
            result[i][j] = mat[j][i];
        }
    }
}

void MatrixSubmatrix(int i, int j, float mat[3][3], float result[2][2])
{
    int t = 0;
    int v = 0; 
    for (int r = 0; r < 3; r++) {
        //checks if we are in one of the rows we want to take out,
            //if we aren't then we continue to check the column
        if (r != i) {
            for (int c = 0; c < 3; c++) {
                //checks if we are in one of the columns we want to take out,
                    //if we aren't then we put that value in our submatrix
                if (c != j) {
                    result[t][v] = mat[r][c];
                    v++;
                }
                else {
                    continue;
                }
            } 
        }
        else {
            continue;
        }
        //adds one to the row counter, since there are different rows in the 
            //original matrix than in the created 2x2 matrix, and sets the columns
            //back to 0 so it starts over
        t++;
        v = 0;
    }    
}

//helper function for MatrixDeterminant
float MatrixDeterminant2x2(float mat[2][2])
{
    //this is the math to find the determinant of a 2x2 matrix
    float answer = (mat[0][0] * mat[1][1]) - (mat[0][1] * mat[1][0]);
    return answer; 
}

float MatrixDeterminant(float mat[3][3])
{   
    //declare the 2x2 matrices that will hold the submatrices of the main matrix
    float x[2][2];
    float y[2][2];
    float z[2][2];
    //put each appropriate submatrix in the above 2x2
    MatrixSubmatrix(0, 0, mat, x);
    MatrixSubmatrix(0, 1, mat, y);
    MatrixSubmatrix(0, 2, mat, z);
    //calculate the determinant of each 2x2 and store it in a new float 
    float a = MatrixDeterminant2x2(x);
    float b = MatrixDeterminant2x2(y);
    float c = MatrixDeterminant2x2(z);
    
    //multiply the appropriate float determinant to the number in the matrix
    float answer = (mat[0][0] * a) - (mat[0][1] * b) + (mat[0][2] * c);
    return answer;
}

void MatrixInverse(float mat[3][3], float result[3][3])
{
    float x[2][2];
    float MatrixOfMinors[3][3]= {{}, {}, {}};
    //created the matrix of minors by iterating through each number in the matrices
        //and finding the determinant of the submatrix and putting that determinant
        //in the same spot\.
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            MatrixSubmatrix(i, j, mat, x);
            float y = MatrixDeterminant2x2(x);
            //ADDING THIS IF STATEMET BECAUSE MINE WAS PRINTING -0
            if (y==0) {
                y = fabs(y);
            }
            MatrixOfMinors[i][j] = y;
        }
    }
    //Creates Matrix of Cofactors by multiplying the numbers in the correct 
        //positions by -1, as long as it is not 0.
    if (MatrixOfMinors[0][1] != 0) {
        MatrixOfMinors[0][1] *= -1;
    }
    if (MatrixOfMinors[1][0] != 0) {
        MatrixOfMinors[1][0] *= -1;
    }
    if (MatrixOfMinors[1][2] != 0) {
        MatrixOfMinors[1][2] *= -1;
    }
    if (MatrixOfMinors[2][1] != 0) {
        MatrixOfMinors[2][1] *= -1;
    }
    
    //Creates Adjugate by Transposing the Matrix of Cofactors
    float transpose[3][3];
    MatrixTranspose(MatrixOfMinors, transpose);
    
    float a = MatrixDeterminant(mat);
    float b = (1/a);
    MatrixScalarMultiply(b, transpose, result);
}

//2x2 Matrix equals helper function to test Submatrix
int MatrixCheck(float mat1[2][2], float mat2[2][2]) 
{   
    float z = 0;
    //nested for loops iterate through all values of i and j (row and column)
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            //checks if the number at i, j is the same for both matrices within .0001
                //if it is, then the loop continues to check every value
            z = mat1[i][j] - mat2[i][j]; 
            z = fabs(z);
            if (z < FP_DELTA) {
                continue;   
            }
            //if even one spot is not equal, the function will return 0, or false.
            else {
                return 0;
            }
        }
    }
    //if it all works successfully, function will return 1, or true
    return 1;
}
