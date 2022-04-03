/* 
 * File:   Player.c
 * Author: tanvirsandhu
 *
 * Created on February 28, 2021, 7:14 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "Player.h"

/*
 * 
 */
static uint8_t inv[INVENTORY_SIZE];
int i = 0;
int x = 0;

int AddToInventory(uint8_t item) {
    //if we have space in the inventory, we add the parameter into our inventory and increment the index
    // so next time it starts at the right spot
    if (i < (INVENTORY_SIZE)) {
        inv[i] = item;
        //printf("inventory: %x", inv[i]);
        i += 1;
        return SUCCESS;
    } else {
        return STANDARD_ERROR;
    }
}

int FindInInventory(uint8_t item) {
    //this function iterates through the whole inventory to check if the parameter item has been 
    // obtained, and if it has been, we return success
    for (x = 0; x < INVENTORY_SIZE; x += 1) {
        if (inv[x] == item) {
            return SUCCESS;
        }
    }
    return STANDARD_ERROR;
}
