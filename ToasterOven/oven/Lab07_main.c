/* 
 * File:   Lab07_main.c
 * Author: tanvirsandhu
 *
 * Created on February 20, 2021, 7:43 PM
 */

// **** Include libraries here ****
// Standard libraries
#include <stdio.h>

//CSE13E Support Library
#include "BOARD.h"
#include "Leds.h"
#include "Adc.h"
#include "Ascii.h"
#include "Oled.h"
#include "OledDriver.h"
#include "Buttons.h"

// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>



// **** Set any macros or preprocessor directives here ****
#define TRUE 1
#define FALSE 0
#define LONG_PRESS 1


// **** Set any local typedefs here ****

typedef enum {
    SETUP, SELECTOR_CHANGE_PENDING, COOKING, RESET_PENDING
} OvenState;

typedef struct {
    OvenState state;
    int remainingTime;
    int initialTime;
    int temp;
    int input;
    int buttonPressTime;
    int cookMode;
} OvenData;

OvenData oD;

enum {
    BAKE, TOAST, BROIL, time, temp
};

// **** Declare any datatypes here ****

// **** Define any module-level, global, or external variables here ****

static uint8_t adcEvent = FALSE;
static uint8_t btnEvent = FALSE;
static uint8_t checkEvent = FALSE;
static uint8_t freeRunTime = 0;
static uint8_t startTime = 0;
static uint8_t timer_tick = 0;
static uint8_t timerEvent = TRUE;
static uint8_t elapsed_time = 0;
static uint8_t elapsed_time1 = 0;
static uint8_t countdown = 0;
int i = 1;

// **** Put any helper functions here ****

/*This function will update your OLED to reflect the state .*/

void updateOvenOLED(OvenData ovenData) {
    char string[100];

    const char top[] = "\x01\x01\x01\x01\x01";
    const char topOff[] = "\x02\x02\x02\x02\x02";
    const char bottom[] = "\x03\x03\x03\x03\x03";
    const char bottomOff[] = "\x04\x04\x04\x04\x04";

    //checks the bake time and if the oven is on and prints for BAKE!!
    if ((oD.cookMode == BAKE) && (oD.remainingTime > 0)) {
        //if changing time, the arrow is on time
        if (oD.input == time) {
            //divided by 60 to get the minutes
            int min = oD.remainingTime / 60;
            //the remainder after being divided is the amount of seconds
            int sec = oD.remainingTime % 60;
            sprintf(string, "|%s|\t Mode: BAKE \n|     |\t>Time: %d:%02d\n"
                    "|-----|\t Temp: %d%s\n|%s|", top, min, sec, oD.temp, DEGREE_SYMBOL, bottom);
        }            //if changing temp, the arrow is on temp
        else if (oD.input == temp) {
            int min = oD.remainingTime / 60;
            //the remainder after being divided is the amount of seconds
            int sec = oD.remainingTime % 60;
            sprintf(string, "|%s|\t Mode: BAKE \n|     |\t Time: %d:%02d\n"
                    "|-----|\t>Temp: %d%s\n|%s|", top, min, sec, oD.temp, DEGREE_SYMBOL, bottom);
        }
    }        //checks the bake time and if the oven is off and on time, it prints for BAKE!!
    else if ((oD.cookMode == BAKE) && (oD.input == time)) {
        //divided by 60 to get the minutes
        int minOff = oD.initialTime / 60;
        //the remainder after being divided is the amount of seconds
        int secOff = oD.initialTime % 60;
        sprintf(string, "|%s|\t Mode: BAKE \n|     |\t>Time: %d:%02d\n"
                "|-----|\t Temp: %d%s\n|%s|", topOff, minOff, secOff, oD.temp, DEGREE_SYMBOL, bottomOff);
    }
        //checks the bake time and if the oven is off and on temp, it prints for BAKE!!
    else if ((oD.cookMode == BAKE) && (oD.input == temp)) {
        //divided by 60 to get the minutes
        int minOff = oD.initialTime / 60;
        //the remainder after being divided is the amount of seconds
        int secOff = oD.initialTime % 60;
        sprintf(string, "|%s|\t Mode: BAKE \n|     |\t Time: %d:%02d\n"
                "|-----|\t>Temp: %d%s\n|%s|", topOff, minOff, secOff, oD.temp, DEGREE_SYMBOL, bottomOff);
    }        //checks the bake time and if the oven is on and prints for TOAST!!
    else if ((oD.cookMode == TOAST) && (oD.remainingTime > 0)) {
        //divided by 60 to get the minutes
        int min = oD.remainingTime / 60;
        //the remainder after being divided is the amount of seconds
        int sec = oD.remainingTime % 60;
        sprintf(string, "|%s|\t Mode: TOAST\n|     |\t>Time: %d:%02d\n"
                "|-----|            \n|%s|", topOff, min, sec, bottom);
    }        //if the oven is OFF, it prints the off version for TOAST
    else if (oD.cookMode == TOAST) {
        //divided by 60 to get the minutes
        int min = oD.initialTime / 60;
        //the remainder after being divided is the amount of seconds
        int sec = oD.initialTime % 60;
        sprintf(string, "|%s|\t Mode: TOAST\n|     |\t>Time: %d:%02d\n"
                "|-----|            \n|%s|", topOff, min, sec, bottomOff);
    }        //checks the bake time and if the oven is on and prints for BROIL!!
    else if ((oD.cookMode == BROIL) && (oD.remainingTime > 0)) {
        //divided by 60 to get the minutes
        int min = oD.remainingTime / 60;
        //the remainder after being divided is the amount of seconds
        int sec = oD.remainingTime % 60;
        sprintf(string, "|%s|\t Mode: BROIL\n|     |\t>Time: %d:%02d\n"
                "|-----|\t Temp: 500%s\n|%s|", top, min, sec, DEGREE_SYMBOL, bottomOff);
    }        //if oven is off, it will print the off version of broil
    else if (oD.cookMode == BROIL) {
        //divided by 60 to get the minutes
        int min = oD.initialTime / 60;
        //the remainder after being divided is the amount of seconds
        int sec = oD.initialTime % 60;
        sprintf(string, "|%s|\t Mode: BROIL\n|     |\t>Time: %d:%02d\n"
                "|-----|\t Temp: 500%s\n|%s|", topOff, min, sec, DEGREE_SYMBOL, bottomOff);
    }
    //prints the appropriate string 
    OledDrawString(string);
    OledUpdate();
}

/*This function will execute your state machine.  
 * It should ONLY run if an event flag has been set.*/
void runOvenSM(void) {
    //write your SM logic here.
    switch (oD.state) {
            //sets up each possible case in the beginning
        case SETUP:
            //if the potentiometer has been moved, the corresponding variable is altered
            //  and the OLED is updated
            if (adcEvent == TRUE) {
                if (oD.input == time) {
                    oD.initialTime = ((AdcRead() >> 2) + 1);
                    //printf("%d", oD.initialTime);
                }
                else if (oD.input == temp) {
                    oD.temp = ((AdcRead() >> 2) + 300);
                    //printf("%d", oD.temp);
                }
                updateOvenOLED(oD);
                oD.state = SETUP;
            }
            //if the third button is pressed, we go to the selector change pending case
            // to determine the action
            if (checkEvent & BUTTON_EVENT_3DOWN) {
                startTime = freeRunTime;
                //printf("yee");
                oD.state = SELECTOR_CHANGE_PENDING;
            }
            //if the fourth button is pressed, we go straight into cooking and update
            // the OLED with the cooking version of the oven
            if (checkEvent & BUTTON_EVENT_4DOWN) {
                startTime = freeRunTime;
                updateOvenOLED(oD);
                oD.state = COOKING;
                oD.remainingTime = oD.initialTime;
            }
            updateOvenOLED(oD);
            break;

        case SELECTOR_CHANGE_PENDING:
            oD.buttonPressTime = freeRunTime - startTime;
            //if the third button is pressed...
            if (checkEvent & BUTTON_EVENT_3UP) {
                elapsed_time = oD.buttonPressTime / 5;
                //... and it's a short press, we rotate between the cook modes
                if (elapsed_time < LONG_PRESS) {
                    if (i == 0) {
                        oD.cookMode = BAKE;
                        i = 1;
                    } else if (i == 1) {
                        oD.cookMode = TOAST;
                        i = 2;
                    } else if (i == 2) {
                        oD.cookMode = BROIL;
                        i = 0;
                    }
                    updateOvenOLED(oD);
                    oD.state = SETUP;
                    //if it is a long press, we toggle between the temp and time for bake
                } else {
                    //printf("hi"); 
                    if (oD.input == temp) {
                        oD.input = time;
                    } else {
                        oD.input = temp;
                    }
                    updateOvenOLED(oD);
                    oD.state = SETUP;
                }
            }
            break;

        case COOKING:
            //if the timer is going...
            if (timer_tick == TRUE) {
                //..and the oven is on with more than 0 seconds...
                if (oD.remainingTime > 0) {
                    //... we update the LED bar!
                    
                    //i find out the interval between LEDS by dividing the initial by 8
                    // then i set another variable equal to the interval so that I can manipulate
                    // the interval variable and still add the original value to it each time
                    uint8_t interval = (oD.initialTime / 8);
                    uint8_t original = interval;
                    if (oD.remainingTime == oD.initialTime) {
                        LEDS_SET(0xFF);
                    }
                    if (oD.remainingTime == oD.initialTime - 1) {
                        LEDS_SET(0xFE);
                    }
                    interval += 1;
                    if (oD.remainingTime == oD.initialTime - interval) {
                        LEDS_SET(0xFC);
                    }
                    interval = interval + original;
                    if (oD.remainingTime == oD.initialTime - interval) {
                        LEDS_SET(0xF8);
                    }
                    interval = interval + original;
                    if (oD.remainingTime == oD.initialTime - interval) {
                        LEDS_SET(0xF0);
                    }
                    interval = interval + original;
                    if (oD.remainingTime == oD.initialTime - interval) {
                        LEDS_SET(0xE0);
                    }
                    interval = interval + original;
                    if (oD.remainingTime == oD.initialTime - interval) {
                        LEDS_SET(0xC0);
                    }
                    interval = interval + original;
                    if (oD.remainingTime == oD.initialTime - interval) {
                        LEDS_SET(0x80);
                    }
                    interval = interval + original;
                    if (oD.remainingTime == oD.initialTime - interval) {
                        LEDS_SET(0x00);
                    }


                    oD.buttonPressTime = freeRunTime - startTime;
                    countdown = (oD.buttonPressTime - oD.remainingTime);
                    //i'm pretty sure my countdown is happening a little faster than
                    // it's supposed to but i'm not sure how to fix it...
                    if ((countdown % 5) == 0) {
                        oD.remainingTime -= 1;
                    }
                    oD.state = COOKING;
                    timer_tick = FALSE;
                    updateOvenOLED(oD);
                } else {
                    //reset the LED, update the OLED, and go back to setup
                    //after  the countdown is over
                    LEDS_SET(0x00);
                    updateOvenOLED(oD);
                    oD.state = SETUP;
                }
                //if the fourth button is pressed, we set the startTime to freeRunTime
                // and go to reset_pending
            }
            if (checkEvent & BUTTON_EVENT_4DOWN) {
                startTime = freeRunTime;
                oD.state = RESET_PENDING;
            }
            break;

        case RESET_PENDING:
            //if timer is ticking and the fourth button was long pressed, we return
            // to setup and reset the LED bar
            //  otherwise, we continue cooking!
            if (timer_tick == TRUE) {
                if (checkEvent & BUTTON_EVENT_4UP) {
                    oD.buttonPressTime = freeRunTime - startTime;
                    elapsed_time1 = oD.buttonPressTime / 5;
                    if (elapsed_time1 >= LONG_PRESS) {
                        oD.state = SETUP;
                        LEDS_SET(0x00);
                        updateOvenOLED(oD);
                    } else {
                        oD.state = COOKING;
                        updateOvenOLED(oD);
                    }
                }
            }
            break;
    }
}

int main() {
    BOARD_Init();

    //initialize timers and timer ISRs:
    // <editor-fold defaultstate="collapsed" desc="TIMER SETUP">

    // Configure Timer 2 using PBCLK as input. We configure it using a 1:16 prescalar, so each timer
    // tick is actually at F_PB / 16 Hz, so setting PR2 to F_PB / 16 / 100 yields a .01s timer.

    T2CON = 0; // everything should be off
    T2CONbits.TCKPS = 0b100; // 1:16 prescaler
    PR2 = BOARD_GetPBClock() / 16 / 100; // interrupt at .5s intervals
    T2CONbits.ON = 1; // turn the timer on

    // Set up the timer interrupt with a priority of 4.
    IFS0bits.T2IF = 0; //clear the interrupt flag before configuring
    IPC2bits.T2IP = 4; // priority of  4
    IPC2bits.T2IS = 0; // subpriority of 0 arbitrarily 
    IEC0bits.T2IE = 1; // turn the interrupt on

    // Configure Timer 3 using PBCLK as input. We configure it using a 1:256 prescaler, so each timer
    // tick is actually at F_PB / 256 Hz, so setting PR3 to F_PB / 256 / 5 yields a .2s timer.

    T3CON = 0; // everything should be off
    T3CONbits.TCKPS = 0b111; // 1:256 prescaler
    PR3 = BOARD_GetPBClock() / 256 / 5; // interrupt at .5s intervals
    T3CONbits.ON = 1; // turn the timer on

    // Set up the timer interrupt with a priority of 4.
    IFS0bits.T3IF = 0; //clear the interrupt flag before configuring
    IPC3bits.T3IP = 4; // priority of  4
    IPC3bits.T3IS = 0; // subpriority of 0 arbitrarily 
    IEC0bits.T3IE = 1; // turn the interrupt on;

    // </editor-fold>

    printf("Welcome to taksandh's Lab07 (Toaster Oven).  Compiled on %s %s.", __TIME__, __DATE__);

    //initialize state machine (and anything else you need to init) here
    BOARD_Init();
    LEDS_INIT();
    OledInit();
    AdcInit();

    //initial SETUP variables
    oD.state = SETUP;
    oD.cookMode = BAKE;
    oD.input = time;
    oD.temp = 350;
    oD.initialTime = (AdcRead() >> 2) + 1;
    updateOvenOLED(oD);

    while (1) {
        // Add main loop code here:
        // check for events
        if ((adcEvent == TRUE) || (btnEvent == TRUE)) {
            // on event, run runOvenSM()
            runOvenSM();
            // clear event flags
            adcEvent = FALSE;
            btnEvent = FALSE;
        }
    }
}

/*The 5hz timer is used to update the free-running timer and to generate TIMER_TICK events*/
void __ISR(_TIMER_3_VECTOR, ipl4auto) TimerInterrupt5Hz(void) {
    // Clear the interrupt flag.
    IFS0CLR = 1 << 12;

    //add event-checking code here
    if (timerEvent == TRUE) {
        freeRunTime++;
        timer_tick = TRUE;
    }
}

/*The 100hz timer is used to check for button and ADC events*/
void __ISR(_TIMER_2_VECTOR, ipl4auto) TimerInterrupt100Hz(void) {
    // Clear the interrupt flag.
    IFS0CLR = 1 << 8;

    //add event-checking code here
    if (AdcChanged()) {
        adcEvent = TRUE;
        timer_tick = TRUE;
    }
    if ((BUTTON_EVENT_3DOWN) || (BUTTON_EVENT_3UP) || (BUTTON_EVENT_4DOWN) || (BUTTON_EVENT_4UP)) {
        checkEvent = ButtonsCheckEvents();
        btnEvent = TRUE;
    }

}