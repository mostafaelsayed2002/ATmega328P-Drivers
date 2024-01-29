#include "../include/i2c.h"
#include "../include/reg.h"
#include "../include/common_macros.h"


int main(void) {

  SET_PORT(DDRD);
  I2C i2c;
  i2c.BR=0x62;
  i2c.PRE = PRE_1;
  i2c.INTER = DISABLE;
  i2c.type = I2C_MASTER;
  I2C_init(i2c);
  
  I2C_start();
  I2C_send_SLA_R(0x01);
  PORTD = I2C_masterRead();
  PORTD =7;

  while (1);
  return 0;
}

// int main(void) {

//   SET_BIT(SREG,7);
//   SET_PORT(DDRD);
//   I2C i2c;
//   i2c.BR=12;
//   i2c.PRE = PRE_1; 
//   i2c.INTER = DISABLE;
//   i2c.type = I2C_SLAVE;
//   i2c.slaveAddress = 0x01;
//   I2C_init(i2c);

//   while (1);
//   return 0;
// }














// master transmit



// int main(void) {

//   SET_PORT(DDRD);
//   I2C i2c;
//   i2c.BR=12;
//   i2c.PRE = PRE_1;
//   i2c.INTER = DISABLE;
//   i2c.type = I2C_MASTER;
//   I2C_init(i2c);
  
//   I2C_start();
//   I2C_send_SLA_W(0x01);  
   
//   while (1){
//    I2C_masterWrite(0x99);
//    PORTD = 7; 
//   }
//   return 0;
// }

// int main(void) {

//   SET_PORT(DDRD);
//   I2C i2c;
//   i2c.BR=12;
//   i2c.PRE = PRE_1;
//   i2c.INTER = DISABLE;
//   i2c.type = I2C_SLAVE;
//   i2c.slaveAddress = 0x01;
//   I2C_init(i2c);
 
//   I2C_Check_SLA_W();
//   while (1){
//       PORTD = I2C_slaveRead();
//   }
//   return 0;
// }




