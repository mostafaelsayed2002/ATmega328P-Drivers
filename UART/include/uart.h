/******************************************************************************
 *
 * Module: USART
 *
 * File Name: gpio.h
 *
 * Description: Header file for the AVR USART driver
 *
 * Author: Mostafa Elsayed
 *
 *******************************************************************************/

#ifndef _USART_H_
#define _USART_H_

#include "std_types.h"

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

typedef enum
{
    BPS_2400,
    BPS_4800,
    BPS_9600,
    BPS_14400,
    BPS_19200,
    BPS_28800,
    BPS_38400,
}UART_Baud_Rate;

typedef enum
{   
    DISABLED,
    EVEN,
    ODD
}UART_Parity_Mode;

typedef enum
{   
    ONE_BIT,
    TWO_BIT
}UART_Stop_Bit;

typedef enum
{   
    FIVE_BITS,
    SIX_BITS,
    SEVEN_BITS,
    EIGHT_BITS,
    NINE_BITS
}UART_Character_Size;

typedef enum
{   
   RXINT_ENABLE,
   RXINT_DISABLE
}UART_RX_Interrupt;

typedef enum
{   
   TXINT_ENABLE,
   TXINT_DISABLE
}UART_TX_Interrupt;

typedef struct
{
    UART_Baud_Rate baudRate;
    UART_Parity_Mode parityMode;
    UART_Stop_Bit stopBit;
    UART_Character_Size characterSize;
    UART_TX_Interrupt txInterrupt;
    UART_RX_Interrupt RxInterrupt;
}UART;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

void UART_init(UART * uart);
uint16 UART_receive();
void UART_transmit(uint16);


#endif

