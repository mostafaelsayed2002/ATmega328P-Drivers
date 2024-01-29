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

#ifndef _SPI_H
#define _SPI_H

#include "std_types.h"




/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef enum{
    MASTER,
    SLAVE
}SPI_Type;

typedef enum{
    RISING,
    FALLING
}SPI_Clock_Polarity;

typedef enum{
    SAMPLE,
    SETUP
}SPI_Clock_Phase;


typedef enum{
    F_2,
    F_4,
    F_8,
    F_16,
    F_32,
    F_64,
    F_128    
}SPI_SCK;


typedef enum{
    DIABLE,
    ENABLE
}SPI_Interrupt;


typedef struct
{
    SPI_Type spiType;
    SPI_Clock_Polarity spiClockPolarity;
    SPI_Clock_Phase spiClockPhase;
    SPI_SCK spiSck;
    SPI_Interrupt spiInterrupt;
}SPI;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

void SPI_init(SPI* spi);
uint8 SPI_slaveReceive();
void SPI_slaveTransmit(uint8);

uint8 SPI_masterTxRx(uint8 data);



#endif