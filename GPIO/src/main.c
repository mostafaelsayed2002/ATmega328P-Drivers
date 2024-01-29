#include <gpio.h>
#include <reg.h>
#include <common_macros.h>
#include <util/delay.h>

#define F_CPU 16000000UL

int main(void) {
  /* Here you can setup your MCU */
    
    GPIO_setupPinDirection(PORTB_ID, PIN5_ID ,PORT_OUTPUT);
    GPIO_writePin(PORTB_ID,PIN5_ID,LOW);
  
  /* Here you implement the logic of your MCU's behavior */
  for (;;) {
          GPIO_writePin(PORTB_ID,PIN5_ID,LOW);
          _delay_ms(500);
          GPIO_writePin(PORTB_ID,PIN5_ID,HIGH);
          _delay_ms(500);
  }
  return 0;
}
