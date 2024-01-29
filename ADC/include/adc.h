/******************************************************************************
 *
 * Module: ADC
 *
 * File Name: ADC.h
 *
 * Description: Header file for the AVR ADC driver
 *
 * Author: Mostafa Elsayed
 *
 *******************************************************************************/


#ifndef _ADC_H_
#define _ADC_H_

 #include "std_types.h"

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

typedef enum
{
	AREF,
    AVCC,
    INTERNAL
}ADC_VoltageReference;

typedef enum
{
	ADC0,
    ADC1,
    ADC2,
    ADC3,
    ADC4,
    ADC5,
    ADC6,
    ADC7,
    ADC8,
    GND,
    VBG
}ADC_InputChannel;



typedef enum
{
    ADC_F_2,
    ADC_F_4,
    ADC_F_8,
    ADC_F_16,
    ADC_F_32,
    ADC_F_64,
    ADC_F_128
}ADC_Prescaler;


typedef enum
{
    FREE_RUNNING,
    ANALOG_COMPARATOR,
    EXTERNAL_INTERRUPT0,
    TIMER0_CTCA,
    TIMER0_OVERFLOW,
}ADC_AutoTriggerSource;


typedef enum{
    ADC_INTERRUPT_ENABLE,
    ADC_INTERRUPT_DIABLE
}ADC_Interrupt;



typedef struct 
{
    ADC_VoltageReference voltageReference;
    ADC_InputChannel inputChannel;
    ADC_Prescaler preScaler;
    ADC_AutoTriggerSource autoTriggerSource;
    ADC_Interrupt interrupt;
}ADC;




/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

void ADC_init(ADC* adc);

void ADC_start();

void ADC_changeChannel(ADC_InputChannel inputChannel);

uint16 ADC_read();

#endif