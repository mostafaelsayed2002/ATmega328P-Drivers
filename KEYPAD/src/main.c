#include "../include/common_macros.h"
#include "../include/reg.h"
#include "../include/keypad.h"
#include "../include/gpio.h"



int main(void) {

  /* Here you can setup your MCU */
  SET_BIT(DDRB,5);


  KEYPAD k;
  k.R1.PORT_ID=PORTD_ID;
  k.R2.PORT_ID=PORTD_ID;
  k.R3.PORT_ID=PORTD_ID;
  k.R4.PORT_ID=PORTD_ID;


  k.C1.PORT_ID=PORTD_ID;
  k.C2.PORT_ID=PORTD_ID;
  k.C3.PORT_ID=PORTD_ID;
  k.C4.PORT_ID=PORTD_ID;

  k.R1.PIN_ID=PIN0_ID;
  k.R2.PIN_ID=PIN1_ID;
  k.R3.PIN_ID=PIN2_ID;
  k.R4.PIN_ID=PIN3_ID;

  k.C1.PIN_ID=PIN4_ID;
  k.C2.PIN_ID=PIN5_ID;
  k.C3.PIN_ID=PIN6_ID;
  k.C4.PIN_ID=PIN7_ID;


  /* Here you implement the logic of your MCU's behavior */
  for(;;) {
   
    uint8 ch = KEYPAD_getKeyPressed(&k);
  
    if(ch == '#')
    {
      SET_BIT(PORTB,5);
    }
    else{
      CLEAR_BIT(PORTB,5);
    }

  }

  return 0;
}
