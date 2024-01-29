/******************************************************************************
 *
 * Module: I2C
 *
 * File Name: gpio.h
 *
 * Description: Header file for the AVR I2C driver
 *
 * Author: Mostafa Elsayed
 *
 *******************************************************************************/

#ifndef _I2C_H_
#define _I2C_H_

#include "std_types.h"


/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

//================================= MASTER ==============================
#define START_ACK 0x08
#define REPEATED_START_ACK 0x10
#define SLA_W_ACK 0x18
#define SLA_W_NACK 0x20
#define SLA_R_ACK 0x40
#define SLA_R_NACK 0x48

//Master Transmitter Mode
#define MASTER_DATA_TRANSMITTED_ACK 0x28
#define MASTER_DATA_TRANSMITTED_NACK 0x30
//Master Receiver Mode
#define MASTER_DATA_RECEIVED_ACK 0x50
#define MASTER_DATA_RECEIVED_NACK 0x58
//================================= SLAVE ==============================
#define OWN_SLA_W_ACK 0x60
#define OWN_SLA_R_ACK 0xA8

//SLAVE Transmitter Mode
#define SLAVE_DATA_TRANSMITTED_ACK 0xB8
#define SLAVE_DATA_TRANSMITTED_NACK 0xC0
//SLAVE Receiver Mode
#define SLAVE_DATA_RECEIVED_ACK 0x80
#define SLAVE_DATA_RECEIVED_NACK 0x88
#define STOP_START_RECEIVED 0xA0

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

typedef enum{
    I2C_MASTER,
    I2C_SLAVE
}I2C_type;

typedef enum{
    ENABLE,
    DISABLE
}INTERRUPT;

typedef enum{
    PRE_1,
    PRE_4,
    PRE_16,
    PRE_64
}PRESCALER;


typedef struct 
{
    I2C_type type;
    uint8 BR;
    INTERRUPT INTER;
    PRESCALER PRE;
    uint8 slaveAddress
}I2C;

/*******************************************************************************
 *                              Functions Prototypes                           *
*******************************************************************************/

void I2C_init(I2C i2c);

void I2C_start();

void I2C_repeatedStart();

void I2C_send_SLA_W(uint8 SLA);

void I2C_send_SLA_R(uint8 SLA);

void I2C_masterWrite(uint8 data);

uint8 I2C_masterRead();

void I2C_stop();

void I2C_Check_SLA_W();

void I2C_Check_SLA_R();

void I2C_slaveWrite(uint8 data);

uint8 I2C_slaveRead();




#endif