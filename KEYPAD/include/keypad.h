/******************************************************************************
 *
 * Module: KEYPAD
 *
 * File Name: keypad.h
 *
 * Description: Header file for the AVR KEYPAD driver
 *
 * Author: Mostafa Elsayed
 *
 *******************************************************************************/

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define NUM_ROWS 4
#define NUM_COLS 4

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

typedef struct 
{
   uint8 PORT_ID;
   uint8 PIN_ID;
}KEYPAD_Wire;

typedef struct 
{
    KEYPAD_Wire R1;
    KEYPAD_Wire R2;
    KEYPAD_Wire R3;
    KEYPAD_Wire R4;
    KEYPAD_Wire C1;
    KEYPAD_Wire C2;
    KEYPAD_Wire C3;
    KEYPAD_Wire C4;
}KEYPAD;


/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

uint8 KEYPAD_getKeyPressed(KEYPAD * keypad);


#endif