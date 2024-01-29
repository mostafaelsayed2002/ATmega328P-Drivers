#include "uart.h"


int main(void) {

  /* Here you can setup your MCU */
  UART uart;
  uart.baudRate = BPS_9600;
  uart.characterSize = EIGHT_BITS;
  uart.parityMode = EVEN;
  uart.stopBit = ONE_BIT;
  uart.RxInterrupt = RXINT_DISABLE;
  uart.txInterrupt = TXINT_DISABLE;
  UART_init(&uart);
  /* Here you implement the logic of your MCU's behavior */
  for(;;) {
      UART_transmit(UART_receive());
  }

  return 0;
}
