#include "gpio.h"
#include "common_macros.h"
#include "reg.h"

void GPIO_setupPinDirection(uint8 port_num, uint8 pin_num, GPIO_PinDirectionType direction)
{
    if (port_num < NUM_OF_PORTS && port_num >= 0)
    {
        switch (port_num)
        {
        case PORTB_ID:
            if (pin_num < NUM_OF_PINS_PORTB && pin_num >= 0)
            {
                if (direction == PIN_INPUT)
                {
                    CLEAR_BIT(DDRB, pin_num);
                }
                else
                {
                    SET_BIT(DDRB, pin_num);
                }
            }
            break;
        case PORTC_ID:
            if (pin_num < NUM_OF_PINS_PORTC && pin_num >= 0)
            {
                if (direction == PIN_INPUT)
                {
                    CLEAR_BIT(DDRC, pin_num);
                }
                else
                {
                    SET_BIT(DDRC, pin_num);
                }
            }
            break;
        case PORTD_ID:
            if (pin_num < NUM_OF_PINS_PORTD && pin_num >= 0)
            {
                if (direction == PIN_INPUT)
                {
                    CLEAR_BIT(DDRD, pin_num);
                }
                else
                {
                    SET_BIT(DDRD, pin_num);
                }
            }
            break;
        }
    }
}

void GPIO_writePin(uint8 port_num, uint8 pin_num, uint8 value)
{
    if (port_num < NUM_OF_PORTS && port_num >= 0)
    {
        switch (port_num)
        {
        case PORTB_ID:
            if (pin_num < NUM_OF_PINS_PORTB && pin_num >= 0)
            {
                if (READ_BIT(DDRB, pin_num))
                    if (value == LOW)
                    {
                        CLEAR_BIT(PORTB, pin_num);
                    }
                    else
                    {
                        SET_BIT(PORTB, pin_num);
                    }
            }
            break;
        case PORTC_ID:
            if (pin_num < NUM_OF_PINS_PORTC && pin_num >= 0)
            {
                if (READ_BIT(DDRC, pin_num))
                    if (value == LOW)
                    {
                        CLEAR_BIT(PORTC, pin_num);
                    }
                    else
                    {
                        SET_BIT(PORTC, pin_num);
                    }
            }
            break;
        case PORTD_ID:
            if (pin_num < NUM_OF_PINS_PORTD && pin_num >= 0)
            {
                if (READ_BIT(DDRD, pin_num))
                    if (value == LOW)
                    {
                        CLEAR_BIT(PORTD, pin_num);
                    }
                    else
                    {
                        SET_BIT(PORTD, pin_num);
                    }
            }
            break;
        }
    }
}

uint8 GPIO_readPin(uint8 port_num, uint8 pin_num)
{
    uint8 res;
    if (port_num < NUM_OF_PORTS && port_num >= 0)
    {
        switch (port_num)
        {
        case PORTB_ID:
            if (pin_num < NUM_OF_PINS_PORTB && pin_num >= 0)
            {
                res = READ_BIT(PINB, pin_num);
            }
            break;
        case PORTC_ID:
            if (pin_num < NUM_OF_PINS_PORTC && pin_num >= 0)
            {
                res = READ_BIT(PINC, pin_num);
            }
            break;
        case PORTD_ID:
            if (pin_num < NUM_OF_PINS_PORTD && pin_num >= 0)
            {
                res = READ_BIT(PIND, pin_num);
            }
            break;
        }
        return res;
    }
}

void GPIO_setupPortDirection(uint8 port_num, uint8 direction)
{
    if (port_num < NUM_OF_PORTS && port_num >= 0)
    {
        switch (port_num)
        {
        case PORTB_ID:
            DDRB = direction;
            break;
        case PORTC_ID:
            DDRC = direction;
            break;
        case PORTD_ID:
            DDRD = direction;
            break;
        }
    }
}

void GPIO_writePort(uint8 port_num, uint8 value)
{
    if (port_num < NUM_OF_PORTS && port_num >= 0)
    {
        switch (port_num)
        {
        case PORTB_ID:
            if (DDRB == 0xFF)
                PORTB = value;
            break;
        case PORTC_ID:
            if (DDRC == 0xFF)
                PORTC = value;
            break;
        case PORTD_ID:
            if (DDRD == 0xFF)
                PORTD = value;
            break;
        }
    }
}

uint8 GPIO_readPort(uint8 port_num)
{
    uint8 res;
    if (port_num < NUM_OF_PORTS && port_num >= 0)
    {
        switch (port_num)
        {
        case PORTB_ID:
            res = PINB;
            break;
        case PORTC_ID:
            res = PINC;
            break;
        case PORTD_ID:
            res = PIND;
            break;
        }
    }
    return res;
}

