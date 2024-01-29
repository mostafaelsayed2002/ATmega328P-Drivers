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

// =============== ADC==================
#define ADMUX (*(volatile uint8*)0x7C)

#define REFS1 7
#define REFS0 6
#define ADLAR 5
#define MUX3 3
#define MUX2 2
#define MUX1 1
#define MUX0 0

#define ADCSRA (*(volatile uint8*)0x7A)

#define ADEN 7
#define ADSC 6
#define ADATE 5
#define ADIF 4
#define ADIE 3
#define ADPS2 2
#define ADPS1 1
#define ADPS0 0

#define ADCH (*(volatile uint8*)0x79)
#define ADCL (*(volatile uint8*)0x78)


#define ADCSRB (*(volatile uint8*)0x7B)

#define ACME 6
#define ADTS2 2
#define ADTS1 1
#define ADTS0 0

#define ADCSRB (*(volatile uint8*)0x7E)

#define ADC5D 5
#define ADC4D 4
#define ADC3D 3
#define ADC2D 2
#define ADC1D 1
#define ADC0D 0






//==================USART=======================
#define UDR0 (*(volatile uint8*)0xC6)

#define UCSR0A (*(volatile uint8*)0xC0)
#define RXC0 7
#define TXC0 6
#define UDRE0 5
#define FE0 4
#define DOR0 3
#define UPE0 2
#define U2X0 1
#define MPCM0 0

#define UCSR0B (*(volatile uint8*)0xC1)
#define RXCIE0 7
#define TXCIE0 6
#define UDRIE0 5
#define RXEN0 4
#define TXEN0 3
#define UCSZ02 2
#define RXB80 1
#define TXB80 0

#define UCSR0C (*(volatile uint8*)0xC2)

#define UMSEL01 7
#define UMSEL00 6
#define UPM01 5
#define UPM00 4
#define USBS0 3
#define UCSZ01 2
#define UCSZ00 1
#define UCPOL0 0


#define UBRR0L (*(volatile uint8*)0xC4)
#define UBRR0H (*(volatile uint8*)0xC5)




#endif
