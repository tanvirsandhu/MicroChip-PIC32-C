/* 
 * File:   mml_test.c
 * Author: Tanvir Sandhu (taksandh@ucsc.edu)
 *
 * Created on January 25, 2021, 1:39 AM
 */

// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

//CMPE13 Support Library
#include "BOARD.h"




// User libraries:
#include "MatrixMath.h"


// Module-level variables:
float zero_matrix[3][3] = {{},{},{}};
int MatrixCheck(float mat1[2][2], float mat2[2][2]);
float MatrixDeterminant2x2(float mat[2][2]);


int main()
{
    BOARD_Init();

    printf("Beginning taksandh's mml test harness, compiled on %s %s\n", __DATE__, __TIME__);
    
    //Matrix Print Zero Matrix Test
    printf("Demonstrating MatrixPrint():\n");
    MatrixPrint(zero_matrix);
    printf("\n");
    float z = 0;

    /* Matrix Equal tests
     *
     *///////////////////
    float arr1[3][3] = {{1, 2, 3}, {1, 4, 5}, {3, 6, 9}}; 
    float arr2[3][3] = {{1, 2, 3}, {1, 4, 5}, {3, 6, 9}};
    float arr3[3][3] = {{3, 4, 2}, {2, 7, 8}, {1, 5, 6}}; 
    float arr5[3][3] = {{1.5, 2, 3}, {1, -2, 5}, {3, 6, 9.125}};
    float arr7[3][3] = {{2.25, 1.45, 12.35},{55, 12.0, -2},{-42, 12.56, 0}};
    
    
    int a = MatrixEquals(arr1, arr2); //they are equal (a should return 1)
    
    int b = MatrixEquals(arr1, arr3); //they are NOT equal (b should be 0)
    
    //depending on what is returned, the following prints the corresponding message
    if (a == 1 && b == 0) {
        printf("PASSED (2/2): MatrixEquals()\n");
        z += 1;         //adds one if it passes for the end percentage
    }
    else if (a == 1 && b == 1) {
        printf("PASSED (1/2): MatrixEquals()\n");
    }
    else if (a == 0 && b == 0) {
        printf("PASSED (1/2): MatrixEquals()\n");
    }
    else {
        printf("PASSED (0/2): MatrixEquals()\n");
    }
    
    /* Matrix Add tests
     *
     *///////////////////
    float result[3][3];
    float correct[3][3] = {{2.5, 4, 6}, {2, 2, 10}, {6, 12, 18.125}};
    MatrixAdd(arr1, arr5, result);
    int c = MatrixEquals(result, correct);

    //second test with different arrays
    float result1[3][3];
    float correct1[3][3] = {{4, 6, 5}, {3, 11, 13}, {4, 11, 15}}; 
    MatrixAdd(arr1, arr3, result1);
    int d = MatrixEquals(result1, correct1);
    
    //depending on what is returned, the following prints the corresponding message
    if (c == 1 && d == 1) {
        printf("PASSED (2/2): MatrixAdd()\n");
        z += 1;
    }
    else if (c == 1 && d == 0) {
        printf("PASSED (1/2): MatrixAdd()\n");
    }
    else if (c == 0 && d == 1) {
        printf("PASSED (1/2): MatrixAdd()\n");
    }
    else {
        printf("PASSED (0/2): MatrixAdd()\n");
    }
    
    /* Matrix Multiply tests
     *
     *///////////////////
    float result6[3][3];
    float correct4[3][3] = {{12, 28, 40}, {20, 48, 68}, {36, 84, 120}};
    MatrixMultiply(arr1, arr2, result6);
    int m = MatrixEquals(result6, correct4);
    
    float result7[3][3];
    float incorrect2[3][3] = {{12, 28, 41}, {20, 48, 68}, {36, 84, 120}};
    MatrixMultiply(arr1, arr2, result7);
    int n = MatrixEquals(result7, incorrect2);
    
    //depending on what is returned, the following prints the corresponding message
    if (m == 1 && n == 1) {
        printf("PASSED (1/2): MatrixMultiply()\n");
    }
    else if (m == 1 && n == 0) {
        printf("PASSED (2/2): MatrixMultiply()\n");
        z += 1;
    }
    else if (m == 0 && n == 0) {
        printf("PASSED (1/2): MatrixMultiply()\n");
    }
    else {
        printf("PASSED (0/2): MatrixMultiply()\n");
    }   
    
    /* Matrix Scalar Add tests
     *
     *///////////////////
    int e = 3;
    float result2[3][3];
    float correct2[3][3] = {{5.25, 4.45, 15.35}, {58, 15, 1}, {-39, 15.56, 3}};
    MatrixScalarAdd(e, arr7, result2);
    int f = MatrixEquals(result2, correct2); //f should return 1 since they are equal
    
    float result3[3][3];
    float incorrect[3][3] = {{6, 7, 5}, {5, 9, 11}, {4, 8, 9}};
    MatrixScalarAdd(e, arr3, result3);
    int g = MatrixEquals(result3, incorrect); //g should return 0 since they're not equal
    
    //depending on what is returned, the following prints the corresponding message
    if (f == 1 && g == 0) {
        printf("PASSED (2/2): MatrixScalarAdd()\n");
        z += 1;
    }
    else if (f == 1 && g == 1) {
        printf("PASSED (1/2): MatrixScalarAdd()\n");
    }
    else if (f == 0 && g == 0) {
        printf("PASSED (1/2): MatrixScalarAdd()\n");
    }
    else {
        printf("PASSED (0/2): MatrixScalarAdd()\n");
    }

    /* Matrix Scalar Multiply tests
     *
     *///////////////////
    int h = 2;
    float result4[3][3];
    float correct3[3][3] = {{4.5, 2.9, 24.7}, {110, 24, -4}, {-84, 25.12, 0}}; 
    MatrixScalarMultiply(h, arr7, result4);
    int k = MatrixEquals(result4, correct3); //k should return 1 since they are equal

    float result5[3][3];
    float incorrect1[3][3] = {{6, 8, 4}, {4, 14, 16}, {2, 10, 11}};
    MatrixScalarMultiply(h, arr3, result5);
    int l = MatrixEquals(result5, incorrect1); //l should return 0 since they're not equal
    
    //depending on what is returned, the following prints the corresponding message
    if (k == 1 && l == 0) {
        printf("PASSED (2/2): MatrixScalarMultiply()\n");
        z += 1;
    }
    else if (k == 1 && l == 1) {
        printf("PASSED (1/2): MatrixScalarMultiply()\n");
    }
    else if (k == 0 && l == 0) {
        printf("PASSED (1/2): MatrixScalarMultiply()\n");
    }
    else {
        printf("PASSED (0/2): MatrixScalarMultiply()\n");
    }
    
    /* Matrix Trace tests
    *
    *///////////////////    
    float o = MatrixTrace(arr1);
    float p = MatrixTrace(arr3);
    
    //depending on what is returned, the following prints the corresponding message
    if (o == 14 && p == 16) {
        printf("PASSED (2/2): MatrixTrace()\n");
        z += 1;
    }
    else if (o != 14 && p == 16) {
        printf("PASSED (1/2): MatrixTrace()\n");
    }
    else if (o == 14 && p != 16) {
        printf("PASSED (1/2): MatrixTrace()\n");
    }
    else {
        printf("PASSED (0/2): MatrixTrace()\n");        
    }
    
    /* Matrix Transpose tests
     *
     *///////////////////
    float result8[3][3];
    float correct5[3][3] = {{2.25, 55, -42}, {1.45, 12.0, 12.56}, {12.35, -2, 0}};
    MatrixTranspose(arr7, result8);
    int q = MatrixEquals(result8, correct5);
    
    float result9[3][3];
    float incorrect3[3][3] = {{3, 2, 1}, {4, 7, 5}, {2, 7, 6}};
    MatrixTranspose(arr3, result9);
    int r = MatrixEquals(result9, incorrect3);

    //depending on what is returned, the following prints the corresponding message    
    if (q == 1 && r == 0) {
        printf("PASSED (2/2): MatrixTranspose()\n");
        z += 1;
    }
    else if (q == 1 && r == 1) {
        printf("PASSED (1/2): MatrixTranspose()\n");
    }
    else if (q == 0 && r == 1) {
        printf("PASSED (1/2): MatrixTranspose()\n");
    }
    else {
        printf("PASSED (0/2): MatrixTranspose()\n");        
    }
                               
    /* Matrix Submatrix tests
     *
     *///////////////////   
    float result10[2][2];
    float correct6[2][2] = {{1, 5}, {3, 9}};
    MatrixSubmatrix(0, 1, arr1, result10);
    int s = MatrixCheck(result10, correct6);
    
    float result11[2][2];
    float incorrect4[2][2] = {{3, 2}, {1, 7}};
    MatrixSubmatrix(2, 1, arr3, result11);
    int t = MatrixCheck(result11, incorrect4);
    
    //depending on what is returned, the following prints the corresponding message
    if (s == 1 && t == 0) {
        printf("PASSED (2/2): MatrixSubmatrix()\n");
        z += 1;
    }
    else if (s == 1 && t == 1) {
        printf("PASSED (1/2): MatrixSubmatrix()\n");
    }
    else if (s == 0 && t == 1) {
        printf("PASSED (1/2): MatrixSubmatrix()\n");
    }
    else {
        printf("PASSED (0/2): MatrixSubmatrix()\n");        
    }                              

    /* Matrix Determinant tests
     *
     *///////////////////  
    float u = MatrixDeterminant(arr1);
    float v = MatrixDeterminant(arr3);
    
    //depending on what is returned, the following prints the corresponding message
    if (u == 0 && v == -4) {
        printf("PASSED (2/2): MatrixDeterminant()\n");
        z += 1;
    }
    else if (u == 0 && v != -4) {
        printf("PASSED (1/2): MatrixDeterminant()\n");
    }
    else if (u != 0 &&  v == -4) {
        printf("PASSED (1/2): MatrixDeterminant()\n");
    }
    else {
        printf("PASSED (0/2): MatrixDeterminant()\n");        
    }    
    
    /* Matrix Inverse tests
     *
     */////////////////// 
    float arr4[3][3] = {{3, 0, 2}, {2, 0, -2}, {0, 1, 1}}; 
    float correct7[3][3] = {{0.2, 0.2, 0}, {-0.2, 0.3, 1}, {0.2, -0.3, 0}};
    float result12[3][3];
    MatrixInverse(arr4, result12);
    float w = MatrixEquals(result12, correct7);
     
    float correct8[3][3] = {{-0.5, 3.5, -4.5}, {1, -4, 5}, {-0.75, 2.75, -3.25}};
    float result13[3][3];
    MatrixInverse(arr3, result13);
    float x = MatrixEquals(result13, correct8);
    
    //depending on what is returned, the following prints the corresponding message
    if (w == 1 && x == 1) {
        printf("PASSED (2/2): MatrixInverse()\n");
        z += 1;
    }
    else if (w == 1 && x != 1) {
        printf("PASSED (1/2): MatrixInverse()\n");
    }
    else if (w != 1 &&  x == 1) {
        printf("PASSED (1/2): MatrixInverse()\n");
    }
    else {
        printf("PASSED (0/2): MatrixInverse()\n");        
    } 
    
    printf("--------------------------------\n");
    
    //y holds the percentage of passed tests
    float y = (z/10) * 100;
    printf("%.0f out of 10 tests passed: %.0f%% \n", z, y);
    
    float arr6[3][3] = {{4.125, 3.250, -2.34}, {2.13, 4.568, 24.23}, {12.34, 1.765, 3.69}};
    printf("\n");
    printf("Output of MatrixPrint(): \n");
    printf("\n");
    
    MatrixPrint(arr6);
    printf("\n");
    
    //hardcoded matrix to check print function
    printf("Expected Output of MatrixPrint(): \n");
    printf("__________________________________\n");
    printf("| 4.125000 | 3.250000 | -2.340000 |\n");
    printf("----------------------------------\n");
    printf("| 2.120000 | 4.568000 | 24.230000 |\n");
    printf("----------------------------------\n");
    printf("| 12.340000 | 1.765000 | 3.690000 |\n");
    printf("----------------------------------\n");
    
    
    
    //float arr1[3][3] = {{1, 2, 3}, {1, 4, 5}, {3, 6, 9}}; 
    //float arr2[3][3] = {{1, 2, 3}, {1, 4, 5}, {3, 6, 9}};
    //float arr3[3][3] = {{3, 4, 2}, {2, 7, 8}, {1, 5, 6};
    
    BOARD_End();
    while (1);
}

