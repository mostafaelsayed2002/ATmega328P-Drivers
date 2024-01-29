/******************************************************************************
 *
 * Module: GPIO
 *
 * File Name: timer.h
 *
 * Description: Header file for the AVR TIMER driver
 *
 * Author: Mostafa Elsayed
 *
 *******************************************************************************/

#ifndef TIMER0_H_
#define TIMER0_H_

 #include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define NUM_OF_OVERFLOWS_PER_SECONDE       3
#define NUM_OF_OVERFLOWS_PER_HALF_OF_SECOND      3

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

typedef enum{ 
     NORMAL,
     CTC
}TIMER_Mode;

typedef enum{ 
    NORMAL_COM,
    TOGGLE,
    CLEAR,
    SET
}TIMER_ComMode;

typedef enum{
    F,
    F_8,
    F_64,
    F_256,
    F_1024
}TIMER_Clock;

typedef enum{ 
   POLLING,
   INTERRUPT
}TIMER_ProcessMode;

/*******************************************************************************
 *                               Dynamic Configurations                        *
 *******************************************************************************/

typedef struct 
{
   uint8 initialVal;
   uint8 orcaVal; // --> OCRA
   TIMER_Clock timerClock;
   TIMER_Mode timerMode;
   TIMER_ComMode timerComMode;
   TIMER_ProcessMode processMode;
}TIMER;


typedef struct 
{
   uint16 initialVal;
   uint16 orcaVal; // --> OCRA
   TIMER_Clock timerClock;
   TIMER_Mode timerMode;
   TIMER_ComMode timerComMode;
   TIMER_ProcessMode processMode;
}TIMER1;


extern uint8 g_ticks;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/




/*******************************************************************************
 *                              Timer0 Functions                               *
 *******************************************************************************/

void TIMER0_init( TIMER * Config_Ptr);

void TIMER0_setCallBack( void (* a_ptr )( void));

void TIMER0_deinit();

void TIMER0_delay_ms(uint32);

void TIMER0_delay_us(uint32);

/*******************************************************************************
 *                              Timer1 Functions                               *
 *******************************************************************************/

void TIMER1_init(TIMER1 * Config_Ptr);

void TIMER1_setCallBack ( void (* a_ptr )( void));

void TIMER1_deinit ();

void TIMER1_delay_ms(uint32);

void TIMER1_delay_us(uint32);

/*******************************************************************************
 *                              Timer2 Functions                               *
 *******************************************************************************/

void TIMER2_init(TIMER * Config_Ptr);

void TIMER2_setCallBack( void (* a_ptr )( void));

void TIMER2_deinit ();

void TIMER2_delay_ms(uint32);

void TIMER2_delay_us(uint32);



#endif