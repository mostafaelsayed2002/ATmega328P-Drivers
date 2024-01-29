#include "../include/adc.h"
#include "../include/uart.h"
#include "../include/common_macros.h"
#include "../include/reg.h"



int main(void) {

  ADC adc; 
  adc.autoTriggerSource = FREE_RUNNING;
  adc.inputChannel = ADC0;
  adc.interrupt = DISABLED;
  adc.preScaler = ADC_F_128;
  adc.voltageReference = AVCC;
  ADC_init(&adc);
  
  UART uart;
  uart.baudRate = BPS_9600;
  uart.characterSize = EIGHT_BITS;
  uart.parityMode = EVEN;
  uart.stopBit = ONE_BIT;
  uart.RxInterrupt = RXINT_DISABLE;
  uart.txInterrupt = TXINT_DISABLE;
  UART_init(&uart);

   

  while (1)
  {
      ADC_start();
      uint16 res = ADC_read();
      uint8 resL = res;
      uint8 resH = (res >> 8);
      UART_transmit(res);    
     // UART_transmit(resH);    
  }
  

  return 0;
}
