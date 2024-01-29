#include "keypad.h"
#include "gpio.h"
#include "common_macros.h"
#include "reg.h"

uint8 KEYPAD_getKeyPressed(KEYPAD *keypad)
{

    GPIO_setupPinDirection(keypad->R1.PORT_ID, keypad->R1.PIN_ID, PIN_OUTPUT);
    GPIO_setupPinDirection(keypad->R2.PORT_ID, keypad->R2.PIN_ID, PIN_OUTPUT);
    GPIO_setupPinDirection(keypad->R3.PORT_ID, keypad->R3.PIN_ID, PIN_OUTPUT);
    GPIO_setupPinDirection(keypad->R4.PORT_ID, keypad->R4.PIN_ID, PIN_OUTPUT);

    GPIO_setupPinDirection(keypad->C1.PORT_ID, keypad->C1.PIN_ID, PIN_INPUT);
    GPIO_setupPinDirection(keypad->C2.PORT_ID, keypad->C2.PIN_ID, PIN_INPUT);
    GPIO_setupPinDirection(keypad->C3.PORT_ID, keypad->C3.PIN_ID, PIN_INPUT);

#if (NUM_COLS == 4)

    GPIO_setupPinDirection(keypad->C4.PORT_ID, keypad->C4.PIN_ID, PIN_INPUT);


    static char keys[NUM_ROWS][NUM_COLS] = {
        {'1', '2', '3', 'A'},
        {'4', '5', '6', 'B'},
        {'7', '8', '9', 'C'},
        {'*', '0', '#', 'D'}};

    uint8 in = 1;
    KEYPAD_Wire arr[4] = {keypad->C1, keypad->C2, keypad->C3, keypad->C4};
    for (uint8 i = 0; i < NUM_ROWS; i++)
    {
        GPIO_writePin(keypad->R1.PORT_ID, keypad->R1.PIN_ID, READ_BIT(in, 0));
        GPIO_writePin(keypad->R2.PORT_ID, keypad->R2.PIN_ID, READ_BIT(in, 1));
        GPIO_writePin(keypad->R3.PORT_ID, keypad->R3.PIN_ID, READ_BIT(in, 2));
        GPIO_writePin(keypad->R4.PORT_ID, keypad->R4.PIN_ID, READ_BIT(in, 3));
        for (uint8 j = 0; j < NUM_COLS; j++)
        {
                
            if (GPIO_readPin(arr[j].PORT_ID, arr[j].PIN_ID))
            {
                return keys[i][j];
            }
        }
        in = in << 1;
    }

#endif

#if (NUM_COLS == 3)

    static keys[NUM_ROWS][NUM_COLS] = {
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'},
        {'*', '0', '#'}};

    uint8 in = 1;
    KEYPAD_Wire arr[3] = {keypad->C1, keypad->C2, keypad->C3};
    for (uint8 i = 0; i < NUM_ROWS; i++)
    {
        GPIO_writePin(keypad->R1.PORT_ID, keypad->R1.PIN_ID, READ_BIT(in, 0));
        GPIO_writePin(keypad->R2.PORT_ID, keypad->R2.PIN_ID, READ_BIT(in, 1));
        GPIO_writePin(keypad->R3.PORT_ID, keypad->R3.PIN_ID, READ_BIT(in, 2));
        GPIO_writePin(keypad->R4.PORT_ID, keypad->R4.PIN_ID, READ_BIT(in, 3));
        for (uint8 j = 0; j < NUM_COLS; j++)
        {
            if (GPIO_readPin(arr[j].PORT_ID, arr[j].PIN_ID))
            {
                return keys[i][j];
            }
        }
        in = in << 1;
    }

#endif

    return '-';
}
