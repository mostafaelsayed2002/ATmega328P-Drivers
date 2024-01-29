#include "../include/spi.h"
#include "../include/common_macros.h"
#include "../include/reg.h"

// int main(void) {

//   SPI spi;
//   spi.spiType = MASTER;
//   spi.spiSck = F_128;
//   spi.spiClockPhase = SAMPLE;
//   spi.spiClockPolarity = RISING;
//   spi.spiInterrupt = DIABLE;
//   SPI_init(&spi);

//   SET_PORT(DDRD);

//   SPI_masterTxRx(0x77);
//   PORTD = SPI_masterTxRx(0xFF);

//   for(;;){}
//   return 0;
// }

int main(void) {

  SPI spi;
  spi.spiType = SLAVE;
  spi.spiSck = F_128;
  SPI_init(&spi);
  spi.spiClockPhase = SAMPLE;
  spi.spiClockPolarity = RISING;
  spi.spiInterrupt = DIABLE;

  SET_PORT(DDRD);

  PORTD = SPI_slaveReceive();
  SPI_slaveTransmit(0x77);
  
  for(;;){}
  return 0;
}





