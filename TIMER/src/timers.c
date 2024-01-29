#include "timers.h"
#include "reg.h"
#include "common_macros.h"
#include <avr/interrupt.h>


extern uint8 g_ticks;

// =============== Timer0 Callback ================
static volatile void (*TIMER0_function)(void);
// =============== Timer1 Callback ================
static volatile void (*TIMER1_function)(void);
// =============== Timer2 Callback ================
static volatile void (*TIMER2_function)(void);


// =============== Timer0 Funcitons ================
static void TIMER0_setMode(TIMER *Config_Ptr)
{
    switch (Config_Ptr->timerMode)
    {
    case NORMAL:
        CLEAR_BIT(TCCR0A, WGM00); // Clear WGM00
        CLEAR_BIT(TCCR0A, WGM01); // Clear WGM01
        CLEAR_BIT(TCCR0B, WGM02); // Clear WGM02
        if (Config_Ptr->processMode == INTERRUPT)
            SET_BIT(TIMSK0, TOIE0);// Set TOIE0
        break;
    case CTC:
        CLEAR_BIT(TCCR0A, WGM00); // Clear WGM00
        SET_BIT(TCCR0A, WGM01);   // Set WGM01
        CLEAR_BIT(TCCR0B, WGM02); // Clear WGM02
        if (Config_Ptr->processMode == INTERRUPT)
        {
            SET_BIT(TIMSK0, OCIE0A); // Set OCIE0A
            SET_BIT(TIMSK0, OCIE0B); // Set OCIE0B
        }
        break;
    }
}

static void TIMER0_setCom(TIMER *Config_Ptr)
{
    switch (Config_Ptr->timerComMode)
    {
    case NORMAL_COM:
        CLEAR_BIT(TCCR0A, COM0A1); // COM0A1
        CLEAR_BIT(TCCR0A, COM0A0); // COM0A0
        break;
    case TOGGLE:
        CLEAR_BIT(TCCR0A, COM0A1); // COM0A1
        SET_BIT(TCCR0A, COM0A0);   // COM0A0
        break;
    case CLEAR:
        SET_BIT(TCCR0A, COM0A1);   // COM0A1
        CLEAR_BIT(TCCR0A, COM0A0); // COM0A0
        break;
    case SET:
        SET_BIT(TCCR0A, COM0A1); // COM0A1
        SET_BIT(TCCR0A, COM0A0); // COM0A0
        break;
    }
}

static void TIMER0_setClock(TIMER *Config_Ptr)
{
    switch (Config_Ptr->timerClock)
    {
    case F:
        SET_BIT(TCCR0B, CS00);   // Set CS00
        CLEAR_BIT(TCCR0B, CS01); // Clear CS01
        CLEAR_BIT(TCCR0B, CS02); // Clear CS02
        break;
    case F_8:
        CLEAR_BIT(TCCR0B, CS00); // Clear CS00
        SET_BIT(TCCR0B, CS01);   // Set CS01
        CLEAR_BIT(TCCR0B, CS02); // Clear CS02
        break;
    case F_64:
        SET_BIT(TCCR0B, CS00);   // Set CS00
        SET_BIT(TCCR0B, CS01);   // Set CS01
        CLEAR_BIT(TCCR0B, CS02); // Clear CS02
        break;
    case F_256:
        CLEAR_BIT(TCCR0B, CS00); // Clear CS00
        CLEAR_BIT(TCCR0B, CS01); // Clear CS01
        SET_BIT(TCCR0B, CS02);   // Set CS02
        break;
    case F_1024:
        SET_BIT(TCCR0B, CS00);   // Set CS00
        CLEAR_BIT(TCCR0B, CS01); // Clear CS01
        SET_BIT(TCCR0B, CS02);   // Set CS02
        break;
    }
}

void TIMER0_init(TIMER *Config_Ptr)
{
    CLEAR_BIT(SREG, 7); // Disable the globle int

    TCNT0 = Config_Ptr->initialVal;
    OCR0A = Config_Ptr->orcaVal;

    TIMER0_setMode(Config_Ptr);
    TIMER0_setCom(Config_Ptr);
    TIMER0_setClock(Config_Ptr);

    SET_BIT(SREG, 7); // Enable the globle int
}

void TIMER0_setCallBack(void (*a_ptr)(void))
{
    if (TIMER0_function)
        TIMER0_function = a_ptr;
}

void TIMER0_deinit()
{
    CLEAR_BIT(SREG, 7);   // Disable the globle int
    CLEAR_BIT(TCCR0B, 0); // Clear CS00
    CLEAR_BIT(TCCR0B, 1); // Clear CS01
    CLEAR_BIT(TCCR0B, 2); // Clear CS02
    SET_BIT(SREG, 7);     // Enable the globle int
}

void TIMER0_delay_ms(uint32 Tms)
{
    TIMER0_deinit();
    TIMER t0;
    t0.initialVal = 0;
    t0.orcaVal = 249;
    t0.processMode = POLLING;
    t0.timerClock = F_64;
    t0.timerMode = CTC;
    t0.timerComMode = NORMAL_COM;
    TIMER0_init(&t0);
   
    
    uint32 count = 0;
    while (count < Tms )
    {    
        if( READ_BIT(TIFR0, 0)){
             count++;
             SET_BIT(TIFR0, 0);
        }

    }
}

void TIMER0_delay_us(uint32 Tus)
{
    TIMER0_deinit();
    TIMER t0;
    t0.initialVal = 0;
    t0.orcaVal = 15;
    t0.processMode = POLLING;
    t0.timerClock = F;
    t0.timerMode = CTC;
    t0.timerComMode = NORMAL_COM;
    TIMER0_init(&t0);

    uint32 count = 0;
    while (count < Tus)
    {
        if( READ_BIT(TIFR0, 1)){
             count++;
             SET_BIT(TIFR0, 1);
        }
    }
}

// =============== Timer0 ISRS ================
ISR(TIMER0_COMPA_vect)
{
    if (TIMER0_function)
        TIMER0_function();
}

ISR(TIMER0_COMPB_vect)
{
    if (TIMER0_function)
        TIMER0_function();
}

ISR(TIMER0_OVF_vect)
{
    if (TIMER0_function)
        TIMER0_function();
}


// =============== Timer2 Funcitons ================

static void TIMER2_setMode(TIMER *Config_Ptr)
{
  switch (Config_Ptr->timerMode)
    {
    case NORMAL:
        CLEAR_BIT(TCCR2A, WGM20); // Clear WGM20
        CLEAR_BIT(TCCR2A, WGM21); // Clear WGM21
        CLEAR_BIT(TCCR2B, WGM22); // Clear WGM22
        if (Config_Ptr->processMode == INTERRUPT)
            SET_BIT(TIMSK2, TOIE2);// Set TOIE2
        break;
    case CTC:
        CLEAR_BIT(TCCR2A, WGM20); // Clear WGM20
        SET_BIT(TCCR2A, WGM21);   // Set WGM21
        CLEAR_BIT(TCCR2B, WGM22); // Clear WGM22
        if (Config_Ptr->processMode == INTERRUPT)
        {
            SET_BIT(TIMSK2, OCIE2A); // Set OCIE2A
            SET_BIT(TIMSK2, OCIE2B); // Set OCIE2B
        }
        break;
    }
}

static void TIMER2_setCom(TIMER *Config_Ptr){

 switch (Config_Ptr->timerComMode)
    {
    case NORMAL_COM:
        CLEAR_BIT(TCCR2A, COM2A1); // COM2A1
        CLEAR_BIT(TCCR2A, COM2A0); // COM2A0
        break;
    case TOGGLE:
        CLEAR_BIT(TCCR2A, COM2A1); // COM2A1
        SET_BIT(TCCR2A, COM2A0);   // COM2A0
        break;
    case CLEAR:
        SET_BIT(TCCR2A, COM2A1);   // COM2A1
        CLEAR_BIT(TCCR2A, COM2A0); // COM2A0
        break;
    case SET:
        SET_BIT(TCCR2A, COM2A1); // COM2A1
        SET_BIT(TCCR2A, COM2A0); // COM2A0
        break;
    }
}

static void TIMER2_setClock(TIMER *Config_Ptr){
switch (Config_Ptr->timerClock)
    {
    case F:
        SET_BIT(TCCR2B, CS20);   // Set CS20
        CLEAR_BIT(TCCR2B, CS21); // Clear CS21
        CLEAR_BIT(TCCR2B, CS22); // Clear CS22
        break;
    case F_8:
        CLEAR_BIT(TCCR2B, CS20); // Clear CS20
        SET_BIT(TCCR2B, CS21);   // Set CS21
        CLEAR_BIT(TCCR2B, CS22); // Clear CS22
        break;
    case F_64:
        CLEAR_BIT(TCCR2B, CS20);   // Set CS20
        CLEAR_BIT(TCCR2B, CS21);   // Set CS21
        SET_BIT(TCCR2B, CS22); // Clear CS22
        break;
    case F_256:
        CLEAR_BIT(TCCR2B, CS20); // Clear CS20
        SET_BIT(TCCR2B, CS21); // Clear CS21
        SET_BIT(TCCR2B, CS22);   // Set CS22
        break;
    case F_1024:
        SET_BIT(TCCR2B, CS20);   // Set CS20
        SET_BIT(TCCR2B, CS21); // Clear CS21
        SET_BIT(TCCR2B, CS22);   // Set CS22
        break;
    }
}

void TIMER2_init(TIMER * Config_Ptr){

    CLEAR_BIT(SREG, 7); // Disable the globle int

    TCNT2 = Config_Ptr->initialVal;
    OCR2A = Config_Ptr->orcaVal;

    TIMER2_setMode(Config_Ptr);
    TIMER2_setCom(Config_Ptr);
    TIMER2_setClock(Config_Ptr);

    SET_BIT(SREG, 7); // Enable the globle int
}

void TIMER2_setCallBack(void (* a_ptr )( void)){
    if (TIMER2_function)
        TIMER2_function = a_ptr;
}

void TIMER2_deinit (){
        CLEAR_BIT(TCCR2B, CS20);   // Set CS20
        CLEAR_BIT(TCCR2B, CS21); // Clear CS21
        CLEAR_BIT(TCCR2B, CS22); // Clear CS22
}

void TIMER2_delay_ms(uint32 Tms){
    TIMER2_deinit();
    TIMER t2;
    t2.initialVal = 0;
    t2.orcaVal = 249;
    t2.processMode = POLLING;
    t2.timerClock = F_64;
    t2.timerMode = CTC;
    t2.timerComMode = NORMAL_COM;
    TIMER2_init(&t2);
   
    uint32 count = 0;
    while (count < Tms )
    {    
        if( READ_BIT(TIFR2, 0)){
             count++;
             SET_BIT(TIFR2, 0);
        }

    }
}

void TIMER2_delay_us(uint32 Tus){
    TIMER2_deinit();
    TIMER t2;
    t2.initialVal = 0;
    t2.orcaVal = 15;
    t2.processMode = POLLING;
    t2.timerClock = F;
    t2.timerMode = CTC;
    t2.timerComMode = NORMAL_COM;
    TIMER2_init(&t2);

    uint32 count = 0;
    while (count < Tus)
    {
        if( READ_BIT(TIFR2, 1)){
             count++;
             SET_BIT(TIFR2, 1);
        }
    }
}

// =============== Timer2 ISRS ================
ISR(TIMER2_COMPA_vect)
{
    if (TIMER2_function)
        TIMER2_function();
}

ISR(TIMER2_COMPB_vect)
{
    if (TIMER2_function)
        TIMER2_function();
}

ISR(TIMER2_OVF_vect){
    if (TIMER2_function)
        TIMER2_function();
}



// =============== Timer1 Funcitons ================
static void TIMER1_setMode(TIMER1 *Config_Ptr){
  switch (Config_Ptr->timerMode)
    {
    case NORMAL:
        CLEAR_BIT(TCCR1A, WGM10); // Clear WGM10
        CLEAR_BIT(TCCR1A, WGM11); // Clear WGM11
        CLEAR_BIT(TCCR1B, WGM12); // Clear WGM12
        CLEAR_BIT(TCCR1B,WGM13); // Clear WGM13
        if (Config_Ptr->processMode == INTERRUPT)
            SET_BIT(TIMSK1, TOIE1);// Set TOIE1
        break;
    case CTC:
        CLEAR_BIT(TCCR1A, WGM10); // Clear WGM10
        CLEAR_BIT(TCCR1A, WGM11);   // Set WGM11
        SET_BIT(TCCR1B, WGM12); // Clear WGM12
        CLEAR_BIT(TCCR1B,WGM13); // Clear WGM13
        if (Config_Ptr->processMode == INTERRUPT)
        {
            SET_BIT(TIMSK1, OCIE1A); // Set OCIE1A
            SET_BIT(TIMSK1, OCIE1B); // Set OCIE1B
        }
        break;
    }
}

static void TIMER1_setCom(TIMER *Config_Ptr){
switch (Config_Ptr->timerComMode)
    {
    case NORMAL_COM:
        CLEAR_BIT(TCCR1A, COM1A1); // COM1A1
        CLEAR_BIT(TCCR1A, COM1A0); // COM1A0
        break;
    case TOGGLE:
        CLEAR_BIT(TCCR1A, COM1A1); // COM1A1
        SET_BIT(TCCR1A, COM1A0);   // COM1A0
        break;
    case CLEAR:
        SET_BIT(TCCR1A, COM1A1);   // COM1A1
        CLEAR_BIT(TCCR1A, COM1A0); // COM1A0
        break;
    case SET:
        SET_BIT(TCCR1A, COM1A1); // COM1A1
        SET_BIT(TCCR1A, COM1A0); // COM1A0
        break;
    }
}

static void TIMER1_setClock(TIMER1 *Config_Ptr){

switch (Config_Ptr->timerClock)
    {
    case F:
        SET_BIT(TCCR1B, CS10);   // Set CS10
        CLEAR_BIT(TCCR1B, CS11); // Clear CS11
        CLEAR_BIT(TCCR1B, CS12); // Clear CS12
        break;
    case F_8:
        CLEAR_BIT(TCCR1B, CS10); // Clear CS10
        SET_BIT(TCCR1B, CS11);   // Set CS11
        CLEAR_BIT(TCCR1B, CS12); // Clear CS12
        break;
    case F_64:
        SET_BIT(TCCR1B, CS10);   // Set CS10
        SET_BIT(TCCR1B, CS11);   // Set CS11
        CLEAR_BIT(TCCR1B, CS12); // Clear CS12
        break;
    case F_256:
        CLEAR_BIT(TCCR1B, CS10); // Clear CS10
        CLEAR_BIT(TCCR1B, CS11); // Clear CS11
        SET_BIT(TCCR1B, CS12);   // Set CS12
        break;
    case F_1024:
        SET_BIT(TCCR1B, CS10);   // Set CS10
        CLEAR_BIT(TCCR1B, CS11); // Clear CS11
        SET_BIT(TCCR1B, CS12);   // Set CS12
        break;
    }
}

void TIMER1_init(TIMER1 * Config_Ptr){
    
    CLEAR_BIT(SREG, 7); // Disable the globle int

    TCNT1 = Config_Ptr->initialVal;
    OCR1A = Config_Ptr->orcaVal;

    TIMER1_setMode(Config_Ptr);
    TIMER1_setCom(Config_Ptr);
    TIMER1_setClock(Config_Ptr);

    SET_BIT(SREG, 7); // Enable the globle int
}

void TIMER1_setCallBack(void (* a_ptr )( void)){
    if (TIMER1_function)
        TIMER1_function = a_ptr;
}

void TIMER1_deinit (){
        CLEAR_BIT(TCCR1B, CS10);   // Clear CS10
        CLEAR_BIT(TCCR1B, CS11); // Clear CS11
        CLEAR_BIT(TCCR1B, CS12); // Clear CS12
}

void TIMER1_delay_ms(uint32 Tms){
    TIMER1_deinit();
    TIMER t1;
    t1.initialVal = 0;
    t1.orcaVal = 249;
    t1.processMode = POLLING;
    t1.timerClock = F_64;
    t1.timerMode = CTC;
    t1.timerComMode = NORMAL_COM;
    TIMER1_init(&t1);
   
    uint32 count = 0;
    while (count < Tms )
    {    
        if( READ_BIT(TIFR2, 0)){
             count++;
             SET_BIT(TIFR2, 0);
        }

    }
}

void TIMER1_delay_us(uint32 Tus){
    TIMER1_deinit();
    TIMER t1;
    t1.initialVal = 0;
    t1.orcaVal = 15;
    t1.processMode = POLLING;
    t1.timerClock = F;
    t1.timerMode = CTC;
    t1.timerComMode = NORMAL_COM;
    TIMER1_init(&t1);

    uint32 count = 0;
    while (count < Tus)
    {
        if( READ_BIT(TIFR2, 1)){
             count++;
             SET_BIT(TIFR2, 1);
        }
    }
}

// =============== Timer1 ISRS ================
ISR(TIMER1_COMPA_vect)
{
    if (TIMER1_function)
        TIMER1_function();
}

ISR(TIMER1_COMPB_vect)
{
    if (TIMER1_function)
        TIMER1_function();
}

ISR(TIMER1_OVF_vect){
    if (TIMER1_function)
        TIMER1_function();
}
