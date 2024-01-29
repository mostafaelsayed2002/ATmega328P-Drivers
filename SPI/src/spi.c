#include "spi.h"
#include "reg.h"
#include "common_macros.h"

  
static void setClockPolarity(SPI_Clock_Polarity spiClockPolarity){
    switch (spiClockPolarity)
    {
    case RISING:
        CLEAR_BIT(SPCR,CPOL);
        break;
    case FALLING:
        SET_BIT(SPCR,CPOL);
        break;
    }
}

static void setClockPhase(SPI_Clock_Phase spiClockPhase){
     switch (spiClockPhase)
    {
    case SAMPLE:
         CLEAR_BIT(SPCR,CPHA);
        break;
    case SETUP:
         SET_BIT(SPCR,CPHA);
        break;
    }
}

static void setIInterrupt(SPI_Interrupt spiInterrupt){
    switch (spiInterrupt)
    {
    case DIABLE:
        CLEAR_BIT(SPCR,SPIE);
        break;
    case ENABLE: 
        SET_BIT(SPCR,SPIE);
        break;
    }
}

static void setSCK(SPI_SCK spiSck){
    switch (spiSck)
    {
    case F_2:
        CLEAR_BIT(SPCR,SPR0);
        CLEAR_BIT(SPCR,SPR1);
        SET_BIT(SPSR,SPI2X);
        break;
    case F_4:
        CLEAR_BIT(SPCR,SPR0);
        CLEAR_BIT(SPCR,SPR1);
        CLEAR_BIT(SPSR,SPI2X);
        break;
    case F_8:
        SET_BIT(SPCR,SPR0);
        CLEAR_BIT(SPCR,SPR1);
        SET_BIT(SPSR,SPI2X);
        break;
    case F_16:
        SET_BIT(SPCR,SPR0);
        CLEAR_BIT(SPCR,SPR1);
        CLEAR_BIT(SPSR,SPI2X);
        break;
    case F_32:
        CLEAR_BIT(SPCR,SPR0);
        SET_BIT(SPCR,SPR1);
        SET_BIT(SPSR,SPI2X);
        break;
    case F_64:
        SET_BIT(SPCR,SPR0);
        SET_BIT(SPCR,SPR1);
        SET_BIT(SPSR,SPI2X);
        break;
    case F_128:
        SET_BIT(SPCR,SPR0);
        SET_BIT(SPCR,SPR1);
        CLEAR_BIT(SPSR,SPI2X);
        break;
    }
}


void SPI_init(SPI* spi){
    SET_BIT(SPCR,SPE);
    if(spi->spiType == MASTER){
        SET_BIT(DDRB,SS);
        SET_BIT(DDRB,MOSI);
        CLEAR_BIT(DDRB,MISO);
        SET_BIT(DDRB,SCK);  
        SET_BIT(SPCR,MSTR);
        SET_BIT(PORTB,SS);
        setSCK(spi->spiSck);   
    }   
    if(spi->spiType == SLAVE){
        CLEAR_BIT(DDRSPI,SS);
        CLEAR_BIT(DDRSPI,MOSI);
        SET_BIT(DDRSPI,MISO);
        CLEAR_BIT(DDRSPI,SCK);
        CLEAR_BIT(SPCR,MSTR);
    }
    setClockPolarity(spi->spiClockPolarity);
    setClockPhase(spi->spiClockPhase);
    setIInterrupt(spi->spiInterrupt);
    CLEAR_BIT(PORTB,SS);
}

uint8 SPI_slaveReceive(){
    while (!READ_BIT(SPSR,SPIF));
    return SPDR;    
}

void SPI_slaveTransmit(uint8 data){
   SPDR = data;
   while (!READ_BIT(SPSR,SPIF)); 
}

uint8 SPI_masterTxRx(uint8 data){
    SPDR = data;  
    while (!READ_BIT(SPSR,SPIF));
    return SPDR;
}