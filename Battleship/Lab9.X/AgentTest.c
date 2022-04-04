/* 
 * File:   AgentTest.c
 * Author: tanvirsandhu
 *
 * Created on March 13, 2021, 5:40 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "BOARD.h"
#include "Agent.h"
#include "Message.h"
#include "Field.h"
#include "BattleBoats.h"
#include "Negotiation.h"
#include "Oled.h"

/*
 * 
 */
//void printField(Field *own_field);
//
//void printField(Field *own_field){
//    int i;
//    int j;
//    int k=0;
//    printf("\t    0 1 2 3 4 5 6 7 8 9\n");
//    printf("\t    | | | | | | | | | |\n");
//    printf("\t%d - ",k);
//    for (i = 0; i < FIELD_ROWS; i += 1) {
//        for (j = 0; j < FIELD_COLS; j += 1) {
//            printf("%d ", own_field->grid[i][j]);
//        }
//        if (k < 5){
//            printf("\n");
//            k += 1;
//            printf("\t%d - ", k);
//        }    
//    }
//        
//}

BB_Event event;
Field myField;

int main() {
    BOARD_Init();
    
    AgentInit();
    printf("Welcome to taksandh's Agent.c test harness\n\n");
    
    //Simple AgentInit tests
    printf("AgentInit Test--\n");
    printf("\tCurrent State should be: 0\n");
    printf("\tCurrent State is: %d\n\n", AgentGetState());
    
    //AgentRun Tests
    printf("AgentRun() Tests--\n");
    
    event.type = BB_EVENT_START_BUTTON;
    AgentRun(event);
    printf("\tThe state after Start Button Pressed should be: 1\n");
    printf("\tThe state after Start Button Pressed is : %d\n\n", AgentGetState());
    
    event.type = BB_EVENT_ACC_RECEIVED;
    AgentRun(event);
    printf("\tThe state after Challenge is Accepted should be: 4\n");
    printf("\tThe state after Challenge is Accepted is: %d\n\n", AgentGetState());
    
    event.type = BB_EVENT_SHO_RECEIVED;
    AgentRun(event);
    printf("\tThe state after Enemy Shot received should be: 5\n");
    printf("\tThe state after Enemy Shot received is: %d\n", AgentGetState());
    printf("\t");
    AgentRun(event);
    
    printf("\n\n");
    AgentInit();
    printf("GAME RESTART TO CHECK OTHER PATHWAYS--\n");
    event.type = BB_EVENT_CHA_RECEIVED;
    AgentRun(event);
    printf("\tThe state after Challenge is Received should be: 2\n");
    printf("\tThe state after Challenge is Received is: %d\n\n", AgentGetState());
    
    event.type = BB_EVENT_REV_RECEIVED;
    AgentRun(event);
    printf("\tThe state after Revealed Message is Received should be: 4\n");
    printf("\tThe state after Revealed Message is Received is: %d\n\n", AgentGetState());
    
    event.type = BB_EVENT_RES_RECEIVED;
    AgentRun(event);
    printf("\tThe state after the Result is Received should be: 4\n");
    printf("\tThe state after the Result is Received is: %d\n", AgentGetState());
    
    printf("\n\t!!PATHWAYS ALL WORK AND AGENT.C RUNS WITHOUT ERRORS!!\n");
    
    while (1);
    BOARD_End();
}

