/* 
 * File:   Agent.c
 * Author: tanvirsandhu
 *
 * Created on March 12, 2021, 2:35 PM
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
static int turnCount;
static NegotiationData A;
static NegotiationData hashA;
static NegotiationData B;
static AgentState myState;
static Field myField;
static Field oppField;
static GuessData guess;
static uint8_t check;
static int cheat;
static int victory;
static int defeat;

void AgentInit(void) {
    myState = AGENT_STATE_START;
    turnCount = 0;
}

Message AgentRun(BB_Event event) {
    Message output;
    
    switch(myState) {
        case(AGENT_STATE_START):
            if (event.type == BB_EVENT_START_BUTTON) {
                //printf("hi");
                A = (NegotiationData)rand();
                hashA = NegotiationHash(A);
                output.type = MESSAGE_CHA;
                output.param0 = hashA;
                FieldInit(&myField, &oppField);
                FieldAIPlaceAllBoats(&myField);
                //printField(&myField);
//                FieldInit(&myField,&oppField);
//                FieldAIPlaceAllBoats(&myField);
//                printField(&myField);
                
                myState = AGENT_STATE_CHALLENGING;
            }
            if (event.type == BB_EVENT_CHA_RECEIVED) {
                B = (NegotiationData)rand();
                output.type = MESSAGE_ACC;
                output.param0 = B;
                FieldInit(&myField, &oppField);
                FieldAIPlaceAllBoats(&myField);
                
                myState = AGENT_STATE_ACCEPTING;
            }
            break;
            
        case AGENT_STATE_CHALLENGING:
            //printf("yes1");
            if (event.type == BB_EVENT_ACC_RECEIVED) {
                output.type = MESSAGE_REV;
                output.param0 = A;
                //printf("yes");
                if (NegotiateCoinFlip(A, B) == HEADS) {
                    //printf("a");
                    myState = AGENT_STATE_WAITING_TO_SEND;
                } else {
                    //printf("b");
                    myState = AGENT_STATE_DEFENDING;
                }
            }
            break;
            
        case AGENT_STATE_ACCEPTING:
            if (event.type == BB_EVENT_REV_RECEIVED) {
                if (NegotiationVerify(A, hashA) == TRUE) {
                    if (NegotiateCoinFlip(A, B) == HEADS) {
                        myState = AGENT_STATE_DEFENDING;
                    } else {
                        guess = FieldAIDecideGuess(&oppField);
                        output.type = MESSAGE_SHO;
                        output.param0 = guess.row;
                        output.param1 = guess.col;
                        myState = AGENT_STATE_ATTACKING;
                    }
                } else {
                    cheat = TRUE;
                    myState = AGENT_STATE_END_SCREEN;
                }
            }
            break;
            
        case AGENT_STATE_DEFENDING:
            if (event.type == BB_EVENT_SHO_RECEIVED) {
                guess.row = event.param0;
                guess.col = event.param1;
                FieldRegisterEnemyAttack(&myField, &guess);
                        
                output.type = MESSAGE_RES;
                output.param0 = guess.row;
                output.param1 = guess.col;
                output.param2 = guess.result;
                
                check = FieldGetBoatStates(&myField);
                if (check == 0) {
                    defeat = TRUE;
                    myState = AGENT_STATE_END_SCREEN;
                } else {
                    myState = AGENT_STATE_WAITING_TO_SEND;
                }
            }
            break;
            
        case AGENT_STATE_WAITING_TO_SEND:
            if (event.type == BB_EVENT_MESSAGE_SENT) {
                turnCount += 1;
                guess = FieldAIDecideGuess(&oppField);
                output.type = MESSAGE_SHO;
                output.param0 = guess.row;
                output.param1 = guess.col;
                myState = AGENT_STATE_ATTACKING;
            } 
            break;
            
        case AGENT_STATE_ATTACKING:
            if (event.type == BB_EVENT_RES_RECEIVED) {
                FieldUpdateKnowledge(&oppField, &guess);
                check = FieldGetBoatStates(&oppField);
                if (check == 0) {
                    victory = TRUE;
                    myState = AGENT_STATE_END_SCREEN;
                } else {
                    myState = AGENT_STATE_DEFENDING;
                }
            }
            break;
            
        case AGENT_STATE_SETUP_BOATS:
            //hehe 
            
        case AGENT_STATE_END_SCREEN:
            if (cheat == TRUE) {
                //cheat message display
                OledInit();
                OledDrawString("CHEATING DETECTED!");
                OledUpdate();
            } else if (defeat == TRUE) {
                //defeat message display
                OledInit();
                OledDrawString("DEFEAT!");
                OledUpdate();
            } else if (victory == TRUE) {
                //victory message display
                OledInit();
                OledDrawString("VICTORY!");
                OledUpdate();
            }
            
    } 
    return output;
}

AgentState AgentGetState(void) {
    return myState;
}

void AgentSetState(AgentState newState) {
    myState = newState;
    return;
}
