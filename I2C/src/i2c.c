#include "i2c.h"
#include "reg.h"
#include "common_macros.h"

static void setPrescaler(PRESCALER PRE){
    switch (PRE)
    {
    case PRE_1:
        CLEAR_BIT(TWSR,TWPS0);
        CLEAR_BIT(TWSR,TWPS1);
        break;
    case PRE_4:
        SET_BIT(TWSR,TWPS0);
        CLEAR_BIT(TWSR,TWPS1);
        break;
    case PRE_16:
        CLEAR_BIT(TWSR,TWPS0);
        SET_BIT(TWSR,TWPS1);
        break;
    case PRE_64:
        SET_BIT(TWSR,TWPS0);
        SET_BIT(TWSR,TWPS1);
        break;    
    }
}

static void setINTERRUPT(INTERRUPT INTER){
    switch (INTER)
    {
    case ENABLE:
        SET_BIT(TWCR,TWIE);
        break;
    case DISABLE:
        CLEAR_BIT(TWCR,TWIE);
        break;
    }
}

void I2C_init(I2C i2c){    
    setINTERRUPT(i2c.INTER);
    SET_BIT(TWCR,TWEN); //enable i2c 
    SET_BIT(TWCR,TWEA); //enable ack

    if(i2c.type == I2C_MASTER)
    {
        setPrescaler(i2c.PRE);
        TWBR = i2c.BR;
    }
    if (i2c.type == I2C_SLAVE)
    {   
         TWCR = 0b01000100;
         TWAR = (i2c.slaveAddress<<1);
         SET_BIT(TWCR,TWIE); //enable interrupt
    }
}

void I2C_start(){
    SET_BIT(TWCR,TWINT);    
    SET_BIT(TWCR,TWSTA);
    SET_BIT(TWCR,TWEN);
    while (!READ_BIT(TWCR ,TWINT));
    while ((TWSR &0xF8) != START_ACK);
}

void I2C_repeatedStart(){
    SET_BIT(TWCR,TWINT);
    SET_BIT(TWCR,TWSTA);
    SET_BIT(TWCR,TWEN);
    while (!READ_BIT(TWCR ,TWINT));
    while ((TWSR &0xF8) != REPEATED_START_ACK);
}

void I2C_send_SLA_W(uint8 SLA)
{
    TWDR = (SLA<<1);
    SET_BIT(TWCR,TWINT);
    SET_BIT(TWCR,TWEN);
    while (!READ_BIT(TWCR ,TWINT)); 
    while ((TWSR &0xF8) != SLA_W_ACK);  
}

void I2C_send_SLA_R(uint8 SLA){
    TWDR = (SLA<<1);
    SET_BIT(TWDR,0);
    SET_BIT(TWCR,TWINT);
    SET_BIT(TWCR,TWEN);
    while (!READ_BIT(TWCR ,TWINT));
    while ((TWSR &0xF8) != SLA_R_ACK);
}

void I2C_masterWrite(uint8 data){ 
   TWDR = data;
   SET_BIT(TWCR,TWINT);
   SET_BIT(TWCR,TWEN);
   while (!READ_BIT(TWCR ,TWINT));
   while ((TWSR &0xF8) != MASTER_DATA_TRANSMITTED_ACK);
}

uint8 I2C_masterRead(){
    SET_BIT(TWCR,TWINT);
    SET_BIT(TWCR,TWEN);
     TWDR = 0xff;
    while (!READ_BIT(TWCR ,TWINT));
    PORTD =7;
    while ((TWSR &0xF8) != MASTER_DATA_RECEIVED_ACK);
    return TWDR;
}

void I2C_stop(){
    SET_BIT(TWCR,TWINT);
    SET_BIT(TWCR,TWSTO);
}

void I2C_Check_SLA_W(){
    SET_BIT(TWCR,TWINT);
    SET_BIT(TWCR,TWEN);
    SET_BIT(TWCR,TWEA);
    while (!READ_BIT(TWCR ,TWINT));
    while ((TWSR &0xF8) != OWN_SLA_W_ACK);    
}

void I2C_Check_SLA_R(){
    SET_BIT(TWCR,TWINT);
    SET_BIT(TWCR,TWEN);
    SET_BIT(TWCR,TWEA);
    while (!READ_BIT(TWCR ,TWINT));
    while ((TWSR &0xF8) != OWN_SLA_R_ACK);
}

void I2C_slaveWrite(uint8 data){
   while (!READ_BIT(TWCR ,TWINT));
   TWDR = data;
   SET_BIT(TWCR,TWINT);
   SET_BIT(TWCR,TWEN);
   SET_BIT(TWCR,TWEA);
   while (!READ_BIT(TWCR ,TWINT));
   PORTD =7;
   while ((TWSR &0xF8) != SLAVE_DATA_TRANSMITTED_ACK);
}

uint8 I2C_slaveRead(){
    SET_BIT(TWCR,TWINT);
    SET_BIT(TWCR,TWEN);
    SET_BIT(TWCR,TWEA);
    while (!READ_BIT(TWCR ,TWINT));
    while ((TWSR &0xF8) != SLAVE_DATA_RECEIVED_ACK);
    return TWDR;
}

