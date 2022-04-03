/* 
 * File:   Player.c
 * Author: tanvirsandhu
 *
 * Created on February 28, 2021, 7:14 PM
 */

// **** Include libraries here ****
// Standard libraries
#include <string.h>
#include <math.h>
#include <stdio.h>
#include "Game.h"
#include "Player.h"

//CSE013E Support Library
#include "UNIXBOARD.h"



// User libraries


// **** Set any macros or preprocessor directives here ****
#define one 1

// **** Declare any data types here ****

// **** Define any global or external variables here ****

// **** Declare any function prototypes here ****

int main()
{



    /******************************** Your custom code goes below here ********************************/
    char title[GAME_MAX_ROOM_TITLE_LENGTH];
    char desc[GAME_MAX_ROOM_DESC_LENGTH];

    //initialize the first room
    if (GameInit() != SUCCESS) {
        FATAL_ERROR();
    }


    while(1) {
        //whichever room we are in, we print its title and description
        GameGetCurrentRoomTitle(title);
        printf("\n\t\t\t\t%s\n\n",title);
        GameGetCurrentRoomDescription(desc);
        printf("%s\n\n", desc);

        //if the exit exists, the corresponding variable will equal one and that is used later for the
        // getchar input
        int a;
        int b;
        int c;
        int d;
        printf("Available Exit(s): ");
        //if the exit is valid, the exit name will be printed after available exits
        if (GameGetCurrentRoomExits() & GAME_ROOM_EXIT_SOUTH_EXISTS) {
            a = one;
            printf("SOUTH ");
        }
        if (GameGetCurrentRoomExits() & GAME_ROOM_EXIT_EAST_EXISTS) {
            b = one;
            printf("EAST ");
        }
        if (GameGetCurrentRoomExits() & GAME_ROOM_EXIT_WEST_EXISTS) {
            c = one;
            printf("WEST ");
        }
        if (GameGetCurrentRoomExits() & GAME_ROOM_EXIT_NORTH_EXISTS) {
            d = one;
            printf("NORTH ");
        }
        //printf("a: %d", a);
        //printf("b: %d", b);
        //printf("c: %d", c);
        //printf("d: %d", d);

        printf("\n\n");
        printf("Which direction would you like to go? (n, s, e, w, q): \n");
        char input = getchar();
        //this line makes sure the char isn't called twice (line given in discord)
        while ((getchar()) != '\n');
        //if the input for the direction is valid and the exit exists, we go in that direction
        // and load up the room
        if ((input == 'n') && (d == 1)) {
            GameGoNorth();
        } else if (input == 's' && a == 1) {
            GameGoSouth();
        } else if (input == 'e' && b == 1) {
            GameGoEast();
        } else if (input == 'w' && c == 1) {
            GameGoWest();
        } else if (input == 'q') {
            break;
        } else {
            printf("Invalid Command!");
        }
    }



    /**************************************************************************************************/
}

