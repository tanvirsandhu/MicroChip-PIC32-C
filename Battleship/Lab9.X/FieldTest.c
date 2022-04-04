/* 
 * File:   FieldTest.c
 * Author: tanvirsandhu
 *
 * Created on March 12, 2021, 10:58 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "BOARD.h"
#include "Field.h"

/*
 * 
 */
void printField(Field *own_field);

void printField(Field *own_field){
    int i;
    int j;
    int k=0;
    printf("\t    0 1 2 3 4 5 6 7 8 9\n");
    printf("\t    | | | | | | | | | |\n");
    printf("\t%d - ",k);
    for (i = 0; i < FIELD_ROWS; i += 1) {
        for (j = 0; j < FIELD_COLS; j += 1) {
            printf("%d ", own_field->grid[i][j]);
        }
        if (k < 5){
            printf("\n");
            k += 1;
            printf("\t%d - ", k);
        }    
    }
        
}

Field myField;
Field oppField; 
GuessData oppGuess;
GuessData myGuess;

int main() {
    BOARD_Init();
    
    
    
    printf("Welcome to taksandh's test harness for Field.c\n\n");
    
    
    //FieldInit Simple Test
    printf("FieldInit() Tests--\n");
    printf("\tOpp Field Before FieldInit: %d\n", oppField.grid[0][0]);
    FieldInit(&myField, &oppField);
    printf("\tOpp Field After FieldInit: %d\n\n", oppField.grid[0][0]);
    
    //FieldGetSquareStatus Tests
    printf("FieldGetSquareStatus() Tests--\n");
    printf("\tStatus of Square on My Field should Be: 0\n");
    printf("\tStatus of Square on My Field Is: %d\n\n", FieldGetSquareStatus(&myField, 0, 0));
    printf("\tStatus of Square on Opp Field should Be: 5\n");
    printf("\tStatus of Square on Opp Field Is: %d\n\n", FieldGetSquareStatus(&oppField, 0, 0));
    printf("\tStatus of Square Outside Bounds should Be: 9\n");
    printf("\tStatus of Square Outside Bounds Is: %d\n\n", FieldGetSquareStatus(&oppField, 12, 12));
    
    //FieldSetSquareStatus Tests
    printf("FieldSetSquareStatus() Tests--\n");
    printf("\tSetting Status of Coordinate (0, 1) to 3\n");
    FieldSetSquareStatus(&myField, 0, 1, FIELD_SQUARE_LARGE_BOAT);
    printf("\tFieldGetSquareStatus(&myField, 0, 1): %d\n\n", FieldGetSquareStatus(&myField, 0, 1));
    printf("\tSetting Status of Coordinate (4, 2) to 2\n");
    FieldSetSquareStatus(&myField, 4, 2, FIELD_SQUARE_MEDIUM_BOAT);
    printf("\tFieldGetSquareStatus(&myField, 4, 2): %d\n\n", FieldGetSquareStatus(&myField, 4, 2));
    
    FieldInit(&myField, &oppField);
    
    //FieldAddBoat Tests
    printf("FieldAddBoat() Tests--\n");
    FieldAddBoat(&myField, 0, 0, FIELD_DIR_SOUTH, FIELD_BOAT_TYPE_HUGE);
    printf("\tField After Adding Huge Boat to (0, 0) towards South: \n");
    printField(&myField);
    printf("\n\tHuge Boat Life Check: ");
    printf("%d\n\n", myField.hugeBoatLives);
    FieldAddBoat(&myField, 4, 6, FIELD_DIR_EAST, FIELD_BOAT_TYPE_SMALL);
    printf("\tField After Adding Small Boat to (4, 6) towards East: \n");
    printField(&myField);
    printf("\n\tSmall Boat Life Check: ");
    printf("%d\n\n", myField.smallBoatLives);
    
    //FieldRegisterEnemyAttacks Test
    printf("FieldRegisterEnemyAttacks() Tests--\n");
    
    oppGuess.row = 4;
    oppGuess.col = 6;
    FieldRegisterEnemyAttack(&myField, &oppGuess);
    printf("\tResult of Square (4,6) after being attacked by Enemy should be: 6\n");
    printf("\tResult of Square (4,6) after being attacked by Enemy is: ");
    printf("%d\n", FieldGetSquareStatus(&myField, 4, 6));
    printf("\tSmall Boat Life Check: ");
    printf("%d\n\n", myField.smallBoatLives);
    
    oppGuess.col = 7;
    FieldRegisterEnemyAttack(&myField, &oppGuess);
    
    oppGuess.col = 8;
    FieldRegisterEnemyAttack(&myField, &oppGuess);
    printf("\tResult of Shot after sinking the Small boat should be: 2\n");
    printf("\tResult of Shot after sinking the Small boat is: ");
    printf("%d\n\n", oppGuess.result);
    
    
    //FieldUpdateKnowledge() Tests
    printf("FieldUpdateKnowledge() Tests--\n");
    printf("\tResult of Hit on (2,3) Enemy Field: \n");
    FieldAddBoat(&oppField, 2, 3, FIELD_DIR_SOUTH, FIELD_BOAT_TYPE_SMALL);
    myGuess.row = 2;
    myGuess.col = 3;
    myGuess.result = RESULT_HIT;
    FieldUpdateKnowledge(&oppField, &myGuess);
    printField(&oppField);
    printf("\n");
    
    //FieldGetBoatStates() Tests
    printf("\nFieldGetBoatStates() Test--\n");
    uint8_t states = FieldGetBoatStates(&myField);
    printf("\tCurrent Boat Status with only the Huge Boat alive Should Be: 8\n");
    printf("\tCurrent Boat Status with only the Huge Boat alive is: ");
    printf("%d\n\n", states);

    //FieldAIPlaceAllBoats Tests
    printf("FieldAIPlaceAllBoats() Test--\n");
    printf("\tFirst Run: \n");
    FieldInit(&myField, &oppField);
    FieldAIPlaceAllBoats(&myField);
    printField(&myField);
    
    printf("\n\n\tSecond Run: \n");
    FieldInit(&myField, &oppField);
    FieldAIPlaceAllBoats(&myField);
    printField(&myField);
    
    //FieldAIDecideGuess Tests
    printf("\n\nFieldAIDecideGuess() Tests--\n");
    myGuess = FieldAIDecideGuess(&oppField);
    printf("My First Guess: (%d, %d)\n", myGuess.row, myGuess.col);
    myGuess = FieldAIDecideGuess(&oppField);
    printf("My Second Guess: (%d, %d)\n\n", myGuess.row, myGuess.col);
    
    
    FieldInit(&myField, &oppField);
    //while(1);
    BOARD_End();
    return SUCCESS;
}

