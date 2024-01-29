#include "uart.h"
#include "common_macros.h"
#include "reg.h"


static void setBaudRate(UART_Baud_Rate baudRate)
{
    switch (baudRate)
    {
    case BPS_2400:
        UBRR0H = (uint8)(2400>>8);
        UBRR0L = (uint8)2400;
         break;
    case BPS_4800:
        UBRR0H = (uint8)(4800>>8);
        UBRR0L = (uint8)4800;
        break;
    case BPS_9600:
        UBRR0H = (uint8)(9600>>8);
        UBRR0L = (uint8)9600;
        break;
    case BPS_14400:
        UBRR0H = (uint8)(14400>>8);
        UBRR0L = (uint8)14400;
        break;
    case BPS_19200:
        UBRR0H = (uint8)(19200>>8);
        UBRR0L = (uint8)19200;
        break;
    case BPS_28800:
        UBRR0H = (uint8)(28800>>8);
        UBRR0L = (uint8)28800;
        break;
    case BPS_38400:
        UBRR0H = (uint8)(38400>>8);
        UBRR0L = (uint8)38400;
        break;
    }
}

static void setParity_Mode(UART_Parity_Mode parityMode){
    switch (parityMode)
    {
    case DISABLED:
        CLEAR_BIT(UCSR0C,UPM00);
        CLEAR_BIT(UCSR0C,UPM01);
        break;
    case EVEN:
        CLEAR_BIT(UCSR0C,UPM00);
        SET_BIT(UCSR0C,UPM01);
        break;
    case ODD:
        SET_BIT(UCSR0C,UPM00);
        SET_BIT(UCSR0C,UPM01);
        break;
    }
}

static void setStopBit(UART_Stop_Bit stopBit){

    switch (stopBit)
    {
    case ONE_BIT:
        CLEAR_BIT(UCSR0C,USBS0);
        break;
    case TWO_BIT:
        SET_BIT(UCSR0C,USBS0);
        break;
    }




}

static void setCharacterSize(UART_Character_Size characterSize){
    switch (characterSize)
    {
    case FIVE_BITS:
        CLEAR_BIT(UCSR0C,UCSZ00);
        CLEAR_BIT(UCSR0C,UCSZ01);
        CLEAR_BIT(UCSR0B,UCSZ02);
        break;
    case SIX_BITS:
        SET_BIT(UCSR0C,UCSZ00);
        CLEAR_BIT(UCSR0C,UCSZ01);
        CLEAR_BIT(UCSR0B,UCSZ02);
        break;    
    case SEVEN_BITS:
        CLEAR_BIT(UCSR0C,UCSZ00);
        SET_BIT(UCSR0C,UCSZ01);
        CLEAR_BIT(UCSR0B,UCSZ02);
        break;
    case EIGHT_BITS:
        SET_BIT(UCSR0C,UCSZ00);
        SET_BIT(UCSR0C,UCSZ01);
        CLEAR_BIT(UCSR0B,UCSZ02);
        break;
    case NINE_BITS:
        SET_BIT(UCSR0C,UCSZ00);
        SET_BIT(UCSR0C,UCSZ01);
        SET_BIT(UCSR0B,UCSZ02);
        break;
    }
}



static void setRxInt(UART_RX_Interrupt RxInterrupt){
    switch (RxInterrupt)
    {
    case RXINT_ENABLE:
        break;
    case RXINT_DISABLE:
        break;
    }

}

static void setTxInt(UART_TX_Interrupt TxInterrupt){
    switch (TxInterrupt)
    {
    case TXINT_ENABLE:
        break;
    case TXINT_DISABLE:
        break;
    }
}

void UART_init(UART * uart){
    CLEAR_BIT(UCSR0C,UMSEL00);
    CLEAR_BIT(UCSR0C,UMSEL01);
    SET_BIT(UCSR0B,TXEN0); 
    SET_BIT(UCSR0B,RXEN0);
    setBaudRate(uart->baudRate);
    setParity_Mode(uart->parityMode);
    setStopBit(uart->stopBit);
    setCharacterSize(uart->characterSize);
    setTxInt(uart->txInterrupt);
    setBaudRate(uart->RxInterrupt);
}

uint16 UART_receive(){
while(!READ_BIT(UCSR0A,RXC0));
return UDR0;
}


void UART_transmit(uint16 data){
while (!READ_BIT(UCSR0A,UDRE0));
UDR0 = data;
}