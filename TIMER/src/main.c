#define __AVR_ATmega328P__
#define F_CPU 16000000
#include "../include/timers.h"
#include "../include/common_macros.h"
#include "../include/reg.h"

int main(void)
{

  
  /* Here you can setup your MCU */
   SET_BIT(DDRB, 5);
   CLEAR_BIT(PORTB, 5);
  /* Here you implement the logic of your MCU's behavior */
  for (;;)
  {
    SET_BIT(PORTB, 5);
    TIMER0_delay_ms(1000);
    CLEAR_BIT(PORTB, 5);
    TIMER0_delay_ms(1000);
  }
  return 0;
}
