#ifndef REG_H_
#define REG_H_


// ================GPIO==================//
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

// ================TIMER0==================//
#define TCCR0A (*(volatile uint8*)0x44)
#define TCCR0B (*(volatile uint8*)0x45)
#define TCNT0 (*(volatile uint8*)0x46)
#define OCR0A (*(volatile uint8*)0x47)
#define OCR0B (*(volatile uint8*)0x48)
#define TIMSK0 (*(volatile uint8*)0x6E)
#define TIFR0 (*(volatile uint8*)0x35)
#define WGM00 0
#define WGM01 1
#define WGM02 3
#define TOIE0 0
#define OCIE0A 1
#define OCIE0B 2
#define COM0A1 7
#define COM0A0 6
#define COM0B1 5
#define COM0B0 4
#define CS00 0
#define CS01 1
#define CS02 2

// ================TIMER1==================//
#define TCCR1A (*(volatile uint8*)0x80)
#define TCCR1B (*(volatile uint8*)0x81)
#define TCNT1 (*(volatile uint16*)0x84)
#define OCR1A (*(volatile uint16*)0x88)
#define OCR1B (*(volatile uint16*)0x8A)
#define TIMSK1 (*(volatile uint8*)0x6F)
#define TIFR1 (*(volatile uint8*)0x36)

#define ICR1 (*(volatile uint8*)0x86)

#define WGM10 0
#define WGM11 1
#define WGM12 3
#define WGM13 4


#define TOIE1 0
#define OCIE1A 1
#define OCIE1B 2

#define COM1A1 7
#define COM1A0 6
#define COM1B1 5
#define COM1B0 4

#define CS10 0
#define CS11 1
#define CS12 2



// ================TIMER2==================//
#define TCCR2A (*(volatile uint8*)0xB0)
#define TCCR2B (*(volatile uint8*)0xB1)
#define TCNT2 (*(volatile uint8*)0xB2)
#define OCR2A (*(volatile uint8*)0xB3)
#define OCR2B (*(volatile uint8*)0xB4)
#define TIMSK2 (*(volatile uint8*)0x70)
#define TIFR2 (*(volatile uint8*)0x37)

#define WGM20 0
#define WGM21 1
#define WGM22 3

#define TOIE2 0
#define OCIE2A 1
#define OCIE2B 2

#define COM2A1 7
#define COM2A0 6
#define COM2B1 5
#define COM2B0 4

#define CS20 0
#define CS21 1
#define CS22 2







#endif
