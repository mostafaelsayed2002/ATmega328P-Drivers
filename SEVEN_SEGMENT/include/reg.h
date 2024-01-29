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


// For Timer0
#define TCCR0A (*(volatile uint8*)0x44)
#define TCCR0B (*(volatile uint8*)0x45)
#define TCNT0 (*(volatile uint8*)0x46)
#define OCR0A (*(volatile uint8*)0x47)
#define OCR0B (*(volatile uint8*)0x48)
#define TIMSK0 (*(volatile uint8*)0x6E)
#define TIFR0 (*(volatile uint8*)0x35)





#endif
