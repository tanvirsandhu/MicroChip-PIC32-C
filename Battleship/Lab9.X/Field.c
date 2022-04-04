/* 
 * File:   Field.c
 * Author: tanvirsandhu
 *
 * Created on March 11, 2021, 3:53 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "BOARD.h"
#include "Field.h"

int randomNumber(int min, int max);

/*
 * 
 */

void FieldInit(Field *own_field, Field * opp_field) {
    int i;
    int j;
    
    for (i = 0; i < FIELD_ROWS; i += 1) {
        for (j = 0; j < FIELD_COLS; j += 1) {
            own_field->grid[i][j] = FIELD_SQUARE_EMPTY;
            opp_field->grid[i][j] = FIELD_SQUARE_UNKNOWN;        
        }
    }
    opp_field->smallBoatLives = FIELD_BOAT_SIZE_SMALL;
    opp_field->mediumBoatLives = FIELD_BOAT_SIZE_MEDIUM;
    opp_field->largeBoatLives = FIELD_BOAT_SIZE_LARGE;
    opp_field->hugeBoatLives = FIELD_BOAT_SIZE_HUGE;
    //srand(time(0));
}

SquareStatus FieldGetSquareStatus(const Field *f, uint8_t row, uint8_t col) {
    if (row < FIELD_ROWS) {
        if (col < FIELD_COLS){
            return f->grid[row][col];
        }
    } else {
        return FIELD_SQUARE_INVALID;
    }
    return SUCCESS;
}
SquareStatus FieldSetSquareStatus(Field *f, uint8_t row, uint8_t col, SquareStatus p) {
    
    SquareStatus oldField = FieldGetSquareStatus(f, row, col);
    
    if (row < FIELD_ROWS) {
        if (col < FIELD_COLS){
            f->grid[row][col] = p;
        }
    }
    return oldField;
}

uint8_t FieldAddBoat(Field *own_field, uint8_t row, uint8_t col, BoatDirection dir, BoatType boat_type) {
    int hugeCheck = 0;
    int largeCheck= 0;
    int mediumCheck= 0;
    int smallCheck= 0;
    BoatSize boat;
    SquareStatus status;
    
    
    if (boat_type == FIELD_BOAT_TYPE_HUGE) {
        boat = FIELD_BOAT_SIZE_HUGE;
        status = FIELD_SQUARE_HUGE_BOAT;
        if (dir == FIELD_DIR_EAST) {
            while (hugeCheck < boat) {
                if (FieldGetSquareStatus(own_field, row, col+hugeCheck) != FIELD_SQUARE_EMPTY) {
                    return STANDARD_ERROR;
                } 
                hugeCheck += 1;   
            }
        } else if (dir == FIELD_DIR_SOUTH) {
            while (hugeCheck < boat) {
                if (FieldGetSquareStatus(own_field, row+hugeCheck, col) != FIELD_SQUARE_EMPTY) {
                    return STANDARD_ERROR;
                } 
                hugeCheck += 1;   
            }
        }
    } else if (boat_type == FIELD_BOAT_TYPE_LARGE) {
        boat = FIELD_BOAT_SIZE_LARGE;
        status = FIELD_SQUARE_LARGE_BOAT;
        if (dir == FIELD_DIR_EAST) {
            while (largeCheck < boat) {
                if (FieldGetSquareStatus(own_field, row, col+largeCheck) != FIELD_SQUARE_EMPTY) {
                    return STANDARD_ERROR;
                } 
                largeCheck += 1;   
            }
        } else if (dir == FIELD_DIR_SOUTH) {
            while (largeCheck < boat) {
                if (FieldGetSquareStatus(own_field, row+largeCheck, col) != FIELD_SQUARE_EMPTY) {
                    return STANDARD_ERROR;
                } 
                largeCheck += 1;   
            }
        }
    } else if (boat_type == FIELD_BOAT_TYPE_MEDIUM) {
        boat = FIELD_BOAT_SIZE_MEDIUM;
        status = FIELD_SQUARE_MEDIUM_BOAT;
        if (dir == FIELD_DIR_EAST) {
            while (mediumCheck < boat) {
                if (FieldGetSquareStatus(own_field, row, col+mediumCheck) != FIELD_SQUARE_EMPTY) {
                    return STANDARD_ERROR;
                } 
                mediumCheck += 1;   
            }
        } else if (dir == FIELD_DIR_SOUTH) {
            while (mediumCheck < boat) {
                if (FieldGetSquareStatus(own_field, row+mediumCheck, col) != FIELD_SQUARE_EMPTY) {
                    return STANDARD_ERROR;
                } 
                mediumCheck += 1;   
            }
        }
    } else if (boat_type == FIELD_BOAT_TYPE_SMALL) {
        boat = FIELD_BOAT_SIZE_SMALL;
        status = FIELD_SQUARE_SMALL_BOAT;
        if (dir == FIELD_DIR_EAST) {
            while (smallCheck < boat) {
                if (FieldGetSquareStatus(own_field, row, col+smallCheck) != FIELD_SQUARE_EMPTY) {
                    return STANDARD_ERROR;
                } 
                smallCheck += 1;   
            }
        } else if (dir == FIELD_DIR_SOUTH) {
            while (smallCheck < boat) {
                if (FieldGetSquareStatus(own_field, row+smallCheck, col) != FIELD_SQUARE_EMPTY) {
                    return STANDARD_ERROR;
                } 
                smallCheck += 1;   
            }
        }
    }
    hugeCheck = 0;
    largeCheck= 0;
    mediumCheck= 0;
    smallCheck= 0;
    if (dir == FIELD_DIR_EAST) {
        if (boat_type == FIELD_BOAT_TYPE_HUGE) {
            own_field->hugeBoatLives = FIELD_BOAT_SIZE_HUGE;
            while (hugeCheck < boat) {
                FieldSetSquareStatus(own_field, row, col+hugeCheck, status);
                hugeCheck += 1;
            }
        } else if (boat_type == FIELD_BOAT_TYPE_LARGE) {
            own_field->largeBoatLives = FIELD_BOAT_SIZE_LARGE;
            while (largeCheck < boat) {
                FieldSetSquareStatus(own_field, row, col+largeCheck, status);
                largeCheck += 1;
            }
        } else if (boat_type == FIELD_BOAT_TYPE_MEDIUM) {
            own_field->mediumBoatLives = FIELD_BOAT_SIZE_MEDIUM;
            while (mediumCheck < boat) {
                FieldSetSquareStatus(own_field, row, col+mediumCheck, status);
                mediumCheck += 1;
            }
        } else if (boat_type == FIELD_BOAT_TYPE_SMALL) {
            
            while (smallCheck < boat) {
                FieldSetSquareStatus(own_field, row, col+smallCheck, status);
                smallCheck += 1;
            }
        }
    }
    if (dir == FIELD_DIR_SOUTH) {
        if (boat_type == FIELD_BOAT_TYPE_HUGE) {
            own_field->largeBoatLives = FIELD_BOAT_SIZE_LARGE;
            while (hugeCheck < boat) {
                FieldSetSquareStatus(own_field, row+hugeCheck, col, status);
                hugeCheck += 1;
            }
        } else if (boat_type == FIELD_BOAT_TYPE_LARGE) {
            while (largeCheck < boat) {
                FieldSetSquareStatus(own_field, row+largeCheck, col, status);
                largeCheck += 1;
            }
        } else if (boat_type == FIELD_BOAT_TYPE_MEDIUM) {
            own_field->mediumBoatLives = FIELD_BOAT_SIZE_MEDIUM;
            while (mediumCheck < boat) {
                FieldSetSquareStatus(own_field, row+mediumCheck, col, status);
                mediumCheck += 1;
            }
        } else if (boat_type == FIELD_BOAT_TYPE_SMALL) {
            while (smallCheck < boat) {
                FieldSetSquareStatus(own_field, row+smallCheck, col, status);
                smallCheck += 1;
            }
        }
    }
    if (boat_type == FIELD_BOAT_TYPE_SMALL) {
        own_field->smallBoatLives = FIELD_BOAT_SIZE_SMALL;
    } else if (boat_type == FIELD_BOAT_TYPE_MEDIUM) {
        own_field->mediumBoatLives = FIELD_BOAT_SIZE_MEDIUM;
    } else if (boat_type == FIELD_BOAT_TYPE_LARGE) {
        own_field->largeBoatLives = FIELD_BOAT_SIZE_LARGE;
    } else if (boat_type == FIELD_BOAT_TYPE_HUGE) {
        own_field->hugeBoatLives = FIELD_BOAT_SIZE_HUGE;
    }
    return SUCCESS;
}

SquareStatus FieldRegisterEnemyAttack(Field *own_field, GuessData *opp_guess) {
    uint8_t beforeAttack = own_field->grid[opp_guess->row][opp_guess->col];
    
    if (own_field->grid[opp_guess->row][opp_guess->col] == FIELD_SQUARE_HUGE_BOAT) {
        if (own_field->hugeBoatLives == 1) {
            own_field->grid[opp_guess->row][opp_guess->col] = FIELD_SQUARE_HIT;
            opp_guess->result = RESULT_HUGE_BOAT_SUNK;
            own_field->hugeBoatLives -= 1;
        } else {
            own_field->grid[opp_guess->row][opp_guess->col] = FIELD_SQUARE_HIT;
            opp_guess->result = RESULT_HIT;
            own_field->hugeBoatLives -= 1;
        }
    } else if (own_field->grid[opp_guess->row][opp_guess->col] == FIELD_SQUARE_LARGE_BOAT) {
        if (own_field->largeBoatLives == 1) {
            own_field->grid[opp_guess->row][opp_guess->col] = FIELD_SQUARE_HIT;
            opp_guess->result = RESULT_LARGE_BOAT_SUNK;
            own_field->largeBoatLives -= 1;
        } else {
            own_field->grid[opp_guess->row][opp_guess->col] = FIELD_SQUARE_HIT;
            opp_guess->result = RESULT_HIT;
            own_field->largeBoatLives -= 1;
        }
    } else if (own_field->grid[opp_guess->row][opp_guess->col] == FIELD_SQUARE_MEDIUM_BOAT) {
        if (own_field->mediumBoatLives == 1) {
            own_field->grid[opp_guess->row][opp_guess->col] = FIELD_SQUARE_HIT;
            opp_guess->result = RESULT_MEDIUM_BOAT_SUNK;
            own_field->mediumBoatLives -= 1;
        } else {
            own_field->grid[opp_guess->row][opp_guess->col] = FIELD_SQUARE_HIT;
            opp_guess->result = RESULT_HIT;
            own_field->mediumBoatLives -= 1;
        }
    } else if (own_field->grid[opp_guess->row][opp_guess->col] == FIELD_SQUARE_SMALL_BOAT) {
        if (own_field->smallBoatLives == 1) {
            own_field->grid[opp_guess->row][opp_guess->col] = FIELD_SQUARE_HIT;
            opp_guess->result = RESULT_SMALL_BOAT_SUNK;
            own_field->smallBoatLives -= 1;
        } else {
            //printf("hi");
            own_field->grid[opp_guess->row][opp_guess->col] = FIELD_SQUARE_HIT;
            opp_guess->result = RESULT_HIT;
            own_field->smallBoatLives -= 1;
            //printf("hello");
        }
    } else if (own_field->grid[opp_guess->row][opp_guess->col] == FIELD_SQUARE_EMPTY) {
        own_field->grid[opp_guess->row][opp_guess->col] = FIELD_SQUARE_MISS;
        opp_guess->result = RESULT_MISS;
    } else {
        own_field->grid[opp_guess->row][opp_guess->col] = FIELD_SQUARE_MISS;
        opp_guess->result = RESULT_MISS;
    }
    return beforeAttack;
}

SquareStatus FieldUpdateKnowledge(Field *opp_field, const GuessData *own_guess) {
    uint8_t prevStatus = opp_field->grid[own_guess->row][own_guess->col];
    
    if (own_guess->result == RESULT_MISS) {
        opp_field->grid[own_guess->row][own_guess->col] = FIELD_SQUARE_EMPTY;
    } else if (own_guess->result == RESULT_HIT) {
        opp_field->grid[own_guess->row][own_guess->col] = FIELD_SQUARE_HIT;
    } else if (own_guess->result == RESULT_HUGE_BOAT_SUNK) {
        opp_field->grid[own_guess->row][own_guess->col] = FIELD_SQUARE_HIT;
        opp_field->hugeBoatLives = 0;
    } else if (own_guess->result == RESULT_LARGE_BOAT_SUNK) {
        opp_field->grid[own_guess->row][own_guess->col] = FIELD_SQUARE_HIT;
        opp_field->largeBoatLives = 0;
    } else if (own_guess->result == RESULT_MEDIUM_BOAT_SUNK) {
        opp_field->grid[own_guess->row][own_guess->col] = FIELD_SQUARE_HIT;
        opp_field->mediumBoatLives = 0;
    } else if (own_guess->result == RESULT_SMALL_BOAT_SUNK) {
        opp_field->grid[own_guess->row][own_guess->col] = FIELD_SQUARE_HIT;
        opp_field->smallBoatLives = 0;
    }
    return prevStatus;
}

uint8_t FieldGetBoatStates(const Field *f) {
    uint8_t bitfield = 0; 
    if (f->hugeBoatLives > 0) {
        bitfield = (bitfield | FIELD_BOAT_STATUS_HUGE);
    } else if (f->largeBoatLives > 0) {
        bitfield = bitfield | FIELD_BOAT_STATUS_LARGE;
    } else if (f->mediumBoatLives > 0) {
        bitfield = bitfield | FIELD_BOAT_STATUS_MEDIUM;
    } else if (f->smallBoatLives > 0) {
        bitfield = bitfield | FIELD_BOAT_STATUS_SMALL;
    }
    return bitfield;
}

//helper function that will generate a random number between 0 and the parameter given
int randomNumber(int min, int max) {
    int random;
    //srand(time(0));
    random = (rand() % (max - min + 1)) + min; 
    return random;
}

uint8_t FieldAIPlaceAllBoats(Field *own_field) {
    //huge boat is always going south in this function
    //large boat is always going east,
    //medium boat is always going south, and
    // small boat is always east.
    uint8_t checker;
    
    while (1) {
        int i = rand() % FIELD_ROWS;
        int j = rand() % FIELD_COLS;
        
        checker = FieldAddBoat(own_field, i, j, FIELD_DIR_SOUTH, FIELD_BOAT_TYPE_HUGE);
        if (checker == SUCCESS){
            break;
        }
    }
    checker = 0;
    while (1) {
        int i = rand() % FIELD_ROWS;
        int j = rand() % FIELD_COLS;
        
        checker = FieldAddBoat(own_field, i, j, FIELD_DIR_EAST, FIELD_BOAT_TYPE_LARGE);
        if (checker == SUCCESS){
            break;
        }
    }
    checker = 0;
    while (1) {
        int i = rand() % FIELD_ROWS;
        int j = rand() % FIELD_COLS;
        
        checker = FieldAddBoat(own_field, i, j, FIELD_DIR_SOUTH, FIELD_BOAT_TYPE_MEDIUM);
        if (checker == SUCCESS){
            break;
        }
    }
    checker = 0;
    while (1) {
        int i = rand() % FIELD_ROWS;
        int j = rand() % FIELD_COLS;
        
        checker = FieldAddBoat(own_field, i, j, FIELD_DIR_EAST, FIELD_BOAT_TYPE_SMALL);
        if (checker == SUCCESS){
            break;
        }
    }
    checker = 0;
    
    return SUCCESS;
}

GuessData FieldAIDecideGuess(const Field *opp_field) {
    GuessData myGuess;
    
    while (1) {
        int i = randomNumber(0, FIELD_ROWS-1);
        int j = randomNumber(0, FIELD_COLS-1);
        
        if (opp_field->grid[i][j] == FIELD_SQUARE_UNKNOWN) {
            myGuess.row = i;
            myGuess.col = j;
            return myGuess;       
        }
    }
}

