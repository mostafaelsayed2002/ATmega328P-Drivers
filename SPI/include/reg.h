#ifndef REG_H_
#define REG_H_


#define PORTB (*(volatile uint8*)0x25)
#define PORTC (*(volatile uint8*)0x28)
#define PORTD (*(volatile uint8*)0x2B)

#define DDRB (*(volatile uint8*)0x24)
#define DDRC (*(volatile uint8*)0x27)
#define DDRD (*(volatile uint8*)0x2A)


#define PINB (*(volatile uint8*)0x23)
#define PINC (*(volatile uint8*)0x26)
#define PIND (*(volatile uint8*)0x29)

//==================SPI=======================

#define SPCR (*(volatile uint8*)0x4C)

// SPIE SPE DORD MSTR CPOL CPHA SPR1 SPR0 

#define SPIE 7
#define SPE  6
#define DORD 5
#define MSTR 4
#define CPOL 3
#define CPHA 2
#define SPR1 1
#define SPR0 0

#define SPSR (*(volatile uint8*)0x4D)

#define SPIF 7
#define WCOL 6
#define SPI2X 0

#define SPDR (*(volatile uint8*)0x4E)

#define DDRSPI (*(volatile uint8*)0x24)

#define SCK 5
#define MISO 4
#define MOSI 3
#define SS 2



#endif
