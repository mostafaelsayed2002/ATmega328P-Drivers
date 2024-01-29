#include "seven_segment.h"
#include "reg.h"
#include "common_macros.h"
#include "gpio.h"

static uint8 arr[7] = {0b00111111,
                       0b00000110,
                       0b01011011,
                       0b01001111,
                       0b01100110,
                       0b01101101,
                       0b01111101,
                       0b00000111,
                       0b01111111,
                       0b01101111,
                       0b01110111,
                       0b01111100,
                       0b00111001,
                       0b01011110,
                       0b01111001,
                       0b01110001};

void SEVEN_SEGMENT_init(SEVEN_SEGMENT *sevenSegment)
{
    GPIO_setupPinDirection(sevenSegment->a.PORT_ID, sevenSegment->a.PIN_ID, PIN_OUTPUT);
    GPIO_setupPinDirection(sevenSegment->b.PORT_ID, sevenSegment->b.PIN_ID, PIN_OUTPUT);
    GPIO_setupPinDirection(sevenSegment->c.PORT_ID, sevenSegment->c.PIN_ID, PIN_OUTPUT);
    GPIO_setupPinDirection(sevenSegment->d.PORT_ID, sevenSegment->d.PIN_ID, PIN_OUTPUT);
    GPIO_setupPinDirection(sevenSegment->e.PORT_ID, sevenSegment->e.PIN_ID, PIN_OUTPUT);
    GPIO_setupPinDirection(sevenSegment->f.PORT_ID, sevenSegment->f.PIN_ID, PIN_OUTPUT);
    GPIO_setupPinDirection(sevenSegment->g.PORT_ID, sevenSegment->g.PIN_ID, PIN_OUTPUT);
    GPIO_setupPinDirection(sevenSegment->DP.PORT_ID, sevenSegment->DP.PIN_ID, PIN_OUTPUT);
}
void SEVEN_SEGMENT_write(SEVEN_SEGMENT *sevenSegment, uint8 val, uint8 valDp)
{
    if (val > 15 || val < 0)
        return;
    GPIO_writePin(sevenSegment->a.PORT_ID, sevenSegment->a.PIN_ID, READ_BIT(arr[val], 0));
    GPIO_writePin(sevenSegment->b.PORT_ID, sevenSegment->b.PIN_ID, READ_BIT(arr[val], 1));
    GPIO_writePin(sevenSegment->b.PORT_ID, sevenSegment->b.PIN_ID, READ_BIT(arr[val], 2));
    GPIO_writePin(sevenSegment->d.PORT_ID, sevenSegment->d.PIN_ID, READ_BIT(arr[val], 3));
    GPIO_writePin(sevenSegment->e.PORT_ID, sevenSegment->e.PIN_ID, READ_BIT(arr[val], 4));
    GPIO_writePin(sevenSegment->f.PORT_ID, sevenSegment->f.PIN_ID, READ_BIT(arr[val], 5));
    GPIO_writePin(sevenSegment->g.PORT_ID, sevenSegment->g.PIN_ID, READ_BIT(arr[val], 6));
    GPIO_writePin(sevenSegment->DP.PORT_ID, sevenSegment->DP.PIN_ID,valDp);
}
