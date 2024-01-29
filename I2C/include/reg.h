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

#define SREG (*(volatile uint8*)0x5F) 

//======================I2C======================

#define TWBR (*(volatile uint8*)0xB8)

#define TWCR (*(volatile uint8*)0xBC)

#define TWINT 7
#define TWEA 6
#define TWSTA 5
#define TWSTO 4
#define TWWC 3
#define TWEN 2
#define TWIE 0


#define TWSR (*(volatile uint8*)0xB9)

#define TWS7 7
#define TWS6 6
#define TWS5 5
#define TWS4 4
#define TWS3 3
#define TWPS1 1
#define TWPS0 0


#define TWDR (*(volatile uint8*)0xBB)

#define TWAR (*(volatile uint8*)0xBA)


#define TWAMR (*(volatile uint8*)0xBD)




#endif
