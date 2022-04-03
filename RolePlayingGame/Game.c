/* 
 * File:   Player.c
 * Author: tanvirsandhu
 *
 * Created on February 28, 2021, 7:14 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Game.h"
#include "Player.h"

#define titleJump 3
#define desJump 2
#define one 1


/*
 * 
 */

struct Game {
    char title[100];
    char description[300];
    //i created a first version and second version of the description for my implementation
    char firstVersion[300];
    char secondVersion[300];
    int northExit;
    int southExit;
    int westExit;
    int eastExit;
} Game;

int newRoom(uint8_t room);

int GameGoNorth(void) {
    //if the exit exists, we load up that room's files that we get from the helper function
    if (GameGetCurrentRoomExits() & GAME_ROOM_EXIT_NORTH_EXISTS) {
        newRoom(Game.northExit);
        //printf("yee");
        return SUCCESS;
    } 
    //otherwise, it'll return error
    return STANDARD_ERROR;
}

int GameGoSouth(void) {
    //if the exit exists, we load up that room's files that we get from the helper function
    if (GameGetCurrentRoomExits() & GAME_ROOM_EXIT_SOUTH_EXISTS) {
        newRoom(Game.southExit);
        //printf("yee");
        return SUCCESS;
    }
    //otherwise, it'll return error
    return STANDARD_ERROR;
}

int GameGoWest(void) {
    //if the exit exists, we load up that room's files that we get from the helper function
    if (GameGetCurrentRoomExits() & GAME_ROOM_EXIT_WEST_EXISTS) {
        newRoom(Game.westExit);
        //printf("yee");
        return SUCCESS;
    }
    //otherwise, it'll return error
    return STANDARD_ERROR;
}

int GameGoEast(void) {
    //if the exit exists, we load up that room's files that we get from the helper function
    if (GameGetCurrentRoomExits() & GAME_ROOM_EXIT_EAST_EXISTS) {
        newRoom(Game.eastExit);
        //printf("yee");
        return SUCCESS;
    }
    //otherwise, it'll return error
    return STANDARD_ERROR;
}

int GameInit(void) {
    //feeds the starting room number to the helper function
    newRoom(STARTING_ROOM);
    //printf("INIT: %s\n", Game.description);
    return SUCCESS;
}

int newRoom(uint8_t newroom) {
    //initialize the four variables
    uint8_t numItemReq = 0;
    uint8_t itemReq = 0;
    uint8_t numItemCont = 0;
    uint8_t itemCont = 0;

    //creating a sprintf so it works for every room once given the room number
    char room[400];
    sprintf(room, "RoomFiles/room%d.txt", newroom);

    //create pointer to hold the file
    FILE *open;
    //opens the file and checks if it successfully opened, otherwise error.
    open = fopen(room, "rb");
    if (open == NULL) {
        FATAL_ERROR();
    }
    //skips the first three letters: RPG
    fseek(open, titleJump, SEEK_SET);
    //gets length of the title
    int titleLen = fgetc(open);
    //reads that length of characters into game.title
    fread(Game.title, 1, titleLen, open);
    Game.title[titleLen] = '\0';

    //holds the num of items required for the first description
    numItemReq = fgetc(open);
    //if there is an item required, then we check what the item is
    if (numItemReq > 0) {
        itemReq = fgetc(open);
        //printf("%x\n", itemReq);
    }
    //skip holds the length of the description
    //printf("%x", numItemReq);
    int skip = fgetc(open);
    //printf("skip: %d", skip);

    //first description is loaded into Game.firstVersion
    fread(Game.firstVersion, one, skip, open);
    Game.firstVersion[skip] = '\0';

    //fseek(open, 2, SEEK_CUR);

    //skips one character to get to the exits, then we hold the exit values into variables
    fseek(open, 1, SEEK_CUR);

    int north1 = fgetc(open);
    int east1 = fgetc(open);
    int south1 = fgetc(open);
    int west1 = fgetc(open);
    //printf("%x\n", north1);
    //printf("%x\n", east1);
    //printf("%x\n", south1);
    //printf("%x\n", west1);

    //now, if there is a second description we load all the values into the correct struct variables
    if (numItemReq > 0) {
        fseek(open, one, SEEK_CUR);
        int desLen = fgetc(open);
        //printf("%x",desLen);
        fread(Game.secondVersion, one, desLen, open);
        Game.secondVersion[desLen] = '\0';
    
        //printf("%s\n", Game.title);
        //printf("%s\n", Game.firstVersion);
        //printf("%s\n", Game.secondVersion);

        numItemCont = fgetc(open);
        if (numItemCont > 0) {
            itemCont = fgetc(open);
            //printf("%x", itemCont);
        }
        //printf("%x", numItemCont);
        int north2 = fgetc(open);
        int east2 = fgetc(open);
        int south2 = fgetc(open);
        int west2 = fgetc(open);
        //printf("%x\n", north2);
        //printf("%x\n", east2);
        //printf("%x\n", south2);
        //printf("%x\n", west2);

        //if there is an item requirements and we have it, then we will print the first description
        if (numItemReq > 0 && (FindInInventory(itemReq) == SUCCESS)) {
            //printf("yoit");
            strcpy(Game.description, Game.firstVersion);
            Game.northExit = north1;
            Game.eastExit = east1;
            Game.southExit = south1;
            Game.westExit = west1;
        //otherwise we print the second version
        } else {
            //printf("yeet");
            strcpy(Game.description, Game.secondVersion);
            Game.northExit = north2;
            Game.eastExit = east2;
            Game.southExit = south2;
            Game.westExit = west2;
        }
    //if there is no item requirement, there is no second description and the correcr first description 
    // values are loaded in
    } else {
        strcpy(Game.description, Game.firstVersion);
            Game.northExit = north1;
            Game.eastExit = east1;
            Game.southExit = south1;
            Game.westExit = west1;
    }


    
    //printf("%s\n", Game.description);
    //printf("%x\n", Game.northExit);
    //printf("%x\n", Game.eastExit);
    //printf("%x\n", Game.southExit);
    //printf("%x\n", Game.westExit);

    //if the room has items, we add the item to the inventory
    if (numItemCont > 0) {
        AddToInventory(itemCont);
    }
    //close the file 
    fclose(open);
    //printf("%s\n", Game.description);
    return SUCCESS;
}

int GameGetCurrentRoomTitle(char *title) {
    //copy the title string from the helper function to the parameter
    strcpy(title, Game.title);
    int x = strlen(title);
    //printf("%s, %d", title, x);
    return x;
}

int GameGetCurrentRoomDescription(char *desc) {
    //copy the description string from the helper function to the parameter
    strcpy(desc, Game.description);
    int x = strlen(desc);
    //printf("%s, %d", desc, x);
    return x;
}

uint8_t GameGetCurrentRoomExits(void) {
    //i tried creating a bitfiels but it didn't work, so I used a uint to or the values 
    uint8_t exit = 0000;
    if (Game.westExit > 0) {
        exit = (exit | GAME_ROOM_EXIT_WEST_EXISTS);
    }
    if (Game.southExit > 0) {
        exit = (exit | GAME_ROOM_EXIT_SOUTH_EXISTS);
    }
    if (Game.eastExit > 0) {
        exit = (exit | GAME_ROOM_EXIT_EAST_EXISTS);
    }
    if (Game.northExit > 0) {
        exit = (exit | GAME_ROOM_EXIT_NORTH_EXISTS);
    }
    return exit;
    //printf("%x", GAME_ROOM_EXIT_WEST_EXISTS);
    //printf("%x", exit);
}
