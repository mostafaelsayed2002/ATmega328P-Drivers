#include "adc.h"
#include "common_macros.h"
#include "reg.h"

static void setPrescaler(ADC_Prescaler prescaler)
{
    switch (prescaler)
    {
    case ADC_F_2:
        CLEAR_BIT(ADCSRA, ADPS0);
        CLEAR_BIT(ADCSRA, ADPS1);
        CLEAR_BIT(ADCSRA, ADPS2);
        break;
    case ADC_F_4:
        CLEAR_BIT(ADCSRA, ADPS0);
        SET_BIT(ADCSRA, ADPS1);
        CLEAR_BIT(ADCSRA, ADPS2);
        break;
    case ADC_F_8:
        SET_BIT(ADCSRA, ADPS0);
        SET_BIT(ADCSRA, ADPS1);
        CLEAR_BIT(ADCSRA, ADPS2);
        break;
    case ADC_F_16:
        CLEAR_BIT(ADCSRA, ADPS0);
        CLEAR_BIT(ADCSRA, ADPS1);
        SET_BIT(ADCSRA, ADPS2);
        break;
    case ADC_F_32:
        SET_BIT(ADCSRA, ADPS0);
        CLEAR_BIT(ADCSRA, ADPS1);
        SET_BIT(ADCSRA, ADPS2);
        break;
    case ADC_F_64:
        CLEAR_BIT(ADCSRA, ADPS0);
        SET_BIT(ADCSRA, ADPS1);
        SET_BIT(ADCSRA, ADPS2);
        break;
    case ADC_F_128:
        SET_BIT(ADCSRA, ADPS0);
        SET_BIT(ADCSRA, ADPS1);
        SET_BIT(ADCSRA, ADPS2);
        break;
    }
}

static void setVoltageReference(ADC_VoltageReference voltageReference)
{
    switch (voltageReference)
    {
    case AREF:
        CLEAR_BIT(ADMUX, REFS0);
        CLEAR_BIT(ADMUX, REFS1);
        break;
    case AVCC:
        SET_BIT(ADMUX, REFS0);
        CLEAR_BIT(ADMUX, REFS1);
        break;
    case INTERNAL:
        SET_BIT(ADMUX, REFS0);
        SET_BIT(ADMUX, REFS1);
        break;
    }
}

static void setAutoTriggerSource(ADC_AutoTriggerSource autoTriggerSource)
{
    switch (autoTriggerSource)
    {
    case FREE_RUNNING:
        CLEAR_BIT(ADCSRB, ADTS0);
        CLEAR_BIT(ADCSRB, ADTS1);
        CLEAR_BIT(ADCSRB, ADTS2);
        break;
    case ANALOG_COMPARATOR:
        SET_BIT(ADCSRA,ADATE);
        SET_BIT(ADCSRB, ADTS0);
        CLEAR_BIT(ADCSRB, ADTS1);
        CLEAR_BIT(ADCSRB, ADTS2);
        break;
    case EXTERNAL_INTERRUPT0:
        SET_BIT(ADCSRA,ADATE);
        CLEAR_BIT(ADCSRB, ADTS0);
        SET_BIT(ADCSRB, ADTS1);
        CLEAR_BIT(ADCSRB, ADTS2);
        break;
    case TIMER0_CTCA:
        SET_BIT(ADCSRA,ADATE);
        SET_BIT(ADCSRB, ADTS0);
        SET_BIT(ADCSRB, ADTS1);
        CLEAR_BIT(ADCSRB, ADTS2);
        break;
    case TIMER0_OVERFLOW:
        SET_BIT(ADCSRA,ADATE);
        CLEAR_BIT(ADCSRB, ADTS0);
        CLEAR_BIT(ADCSRB, ADTS1);
        SET_BIT(ADCSRB, ADTS2);
        break;
    }
}

static void setInterrupt(ADC_Interrupt interrupt){
    switch (interrupt)
    {
    case ADC_INTERRUPT_DIABLE:
        CLEAR_BIT(ADCSRA,ADIE);
        break;
    case ADC_INTERRUPT_ENABLE:
        SET_BIT(ADCSRA,ADIE);
        break;   
    }
}

void ADC_changeChannel(ADC_InputChannel inputChannel)
{
    switch (inputChannel)
    {
    case ADC0:
        CLEAR_BIT(ADMUX, MUX0);
        CLEAR_BIT(ADMUX, MUX1);
        CLEAR_BIT(ADMUX, MUX2);
        CLEAR_BIT(ADMUX, MUX3);
        break;
    case ADC1:
        SET_BIT(ADMUX, MUX0);
        CLEAR_BIT(ADMUX, MUX1);
        CLEAR_BIT(ADMUX, MUX2);
        CLEAR_BIT(ADMUX, MUX3);

        break;
    case ADC2:
        CLEAR_BIT(ADMUX, MUX0);
        SET_BIT(ADMUX, MUX1);
        CLEAR_BIT(ADMUX, MUX2);
        CLEAR_BIT(ADMUX, MUX3);
        break;
    case ADC3:
        SET_BIT(ADMUX, MUX0);
        SET_BIT(ADMUX, MUX1);
        CLEAR_BIT(ADMUX, MUX2);
        CLEAR_BIT(ADMUX, MUX3);
        break;
    case ADC4:
        CLEAR_BIT(ADMUX, MUX0);
        CLEAR_BIT(ADMUX, MUX1);
        SET_BIT(ADMUX, MUX2);
        CLEAR_BIT(ADMUX, MUX3);
        break;
    case ADC5:
        SET_BIT(ADMUX, MUX0);
        CLEAR_BIT(ADMUX, MUX1);
        SET_BIT(ADMUX, MUX2);
        CLEAR_BIT(ADMUX, MUX3);
        break;
    case ADC6:
        CLEAR_BIT(ADMUX, MUX0);
        SET_BIT(ADMUX, MUX1);
        SET_BIT(ADMUX, MUX2);
        CLEAR_BIT(ADMUX, MUX3);
        break;
    case ADC7:
        SET_BIT(ADMUX, MUX0);
        SET_BIT(ADMUX, MUX1);
        SET_BIT(ADMUX, MUX2);
        CLEAR_BIT(ADMUX, MUX3);
        break;
    case ADC8:
        CLEAR_BIT(ADMUX, MUX0);
        CLEAR_BIT(ADMUX, MUX1);
        CLEAR_BIT(ADMUX, MUX2);
        SET_BIT(ADMUX, MUX3);
        break;
    case GND:
        CLEAR_BIT(ADMUX, MUX0);
        SET_BIT(ADMUX, MUX1);
        SET_BIT(ADMUX, MUX2);
        SET_BIT(ADMUX, MUX3);

        break;
    case VBG:
        SET_BIT(ADMUX, MUX0);
        SET_BIT(ADMUX, MUX1);
        SET_BIT(ADMUX, MUX2);
        SET_BIT(ADMUX, MUX3);
        break;
    }
}

void ADC_init(ADC *adc)
{
  SET_BIT(ADCSRA,ADEN); //ADEN: ADC Enable
  setPrescaler(adc->preScaler);
  ADC_changeChannel(adc->inputChannel);
  setVoltageReference(adc->voltageReference);
}

void ADC_start(){
     SET_BIT(ADCSRA,ADSC); //Bit 6 – ADSC: ADC Start Conversion
}


uint16 ADC_read(){
  while (!READ_BIT(ADCSRA,ADIF));  
      SET_BIT(ADCSRA,ADIF);
      uint16 res = 0;
      res |= ADCL;
      res |= (ADCH<<8); 
      return res;
}