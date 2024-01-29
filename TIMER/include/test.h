#ifndef TIMER_1_H
#define TIMER_1_H

#include "../std_types.h"
#include "../common_macros.h"

#define TCNT1 ((volatile u16 *)0x84)
#define OCR1A ((volatile u16 *)0x88)
#define OCR1B ((volatile u16 *)0x8A)
#define ICR1 ((volatile u16 *)0x86)

#define TCCR1A ((volatile u8 *)0x80)
#define COM1A1 7
#define COM1A0 6
#define COM1B1 5
#define COM1B0 4
#define WGM11 1
#define WGM10 0

#define TCCR1B ((volatile u8 *)0x81)
#define ICNC1 7
#define ICES1 6
#define WGM13 4
#define WGM12 3
#define CS12 2
#define CS11 1
#define CS10 0

#define TCCR1C ((volatile u8 *)0x82)
#define FOC1A 7
#define FOC1B 7

#define TIMSK1 ((volatile u8 *)0x6F)
#define ICIE1 5
#define OCIE1B 2
#define OCIE1A 1
#define TOIE1 0

#define TIFR1 ((volatile u8 *)0x36)
#define ICF1 5
#define OCF1A 2
#define OCF1B 1
#define TOV1 0

volatile void (*callback_ptr)(void);

typedef enum
{
    CLK_NO_CLK,
    CLK_F_CPU,
    CLK_F_CPU_8,
    CLK_F_CPU_64,
    CLK_F_CPU_256,
    CLK_F_CPU_1024,
} Timer1_timer_clk;

typedef enum
{
    POLLING,
    INTERRUPT,
} Timer1_operation_mode;

typedef enum
{
    NORMAL_MODE,
    CTC_MODE_OCR1A,
    CTC_MODE_ICR1,
    FAST_PWM_MODE_ICR1,
    FAST_PWM_MODE_OCR1A,
    ICU_MODE
} Timer1_timer_mode;

typedef enum
{
    // Disconnect port OC1A (PB1), OC1B (PB2)
    COM_NORMAL,
    // Toggle port OC1A (PB1), OC1B (PB2) on compare match
    COM_TOGGLE,
    // Clear port OC1A (PB1), OC1B (PB2) on compare match
    COM_NON_INVERTING,
    // Set port OC1A (PB1), OC1B (PB2) on compare match
    COM_INVERTING
} Timer1_com_mode;

typedef enum
{
    RISING_EDGE,
    FALLING_EDGE,
} Timer1_ICU_trigger_edge;

typedef struct
{
    u16 initial_val;
    u16 ocra_val;
    u16 ocrb_val;
    u16 icr1_val;
    u8 ICU_enable_noise_cancelling;
    Timer1_ICU_trigger_edge ICU_edge_behaviour;
    Timer1_operation_mode timer_operation;
    Timer1_timer_clk timer_clk;
    Timer1_timer_mode timer_mode;
    Timer1_com_mode timer_com_mode_a;
    Timer1_com_mode timer_com_mode_b;
} Timer1_config;

static inline void _setTimer1Mode(Timer1_timer_mode timer_mode)
{
    switch (timer_mode)
    {
    case NORMAL_MODE:
        CLEAR_BIT(*TCCR1A, WGM10);
        CLEAR_BIT(*TCCR1A, WGM11);
        CLEAR_BIT(*TCCR1B, WGM12);
        CLEAR_BIT(*TCCR1B, WGM13);
        break;
    case ICU_MODE:
        CLEAR_BIT(*TCCR1A, WGM10);
        CLEAR_BIT(*TCCR1A, WGM11);
        CLEAR_BIT(*TCCR1B, WGM12);
        CLEAR_BIT(*TCCR1B, WGM13);
        break;
    case CTC_MODE_OCR1A:
        CLEAR_BIT(*TCCR1A, WGM10);
        CLEAR_BIT(*TCCR1A, WGM11);
        SET_BIT(*TCCR1B, WGM12);
        CLEAR_BIT(*TCCR1B, WGM13);
        break;
    case CTC_MODE_ICR1:
        CLEAR_BIT(*TCCR1A, WGM10);
        CLEAR_BIT(*TCCR1A, WGM11);
        SET_BIT(*TCCR1B, WGM12);
        SET_BIT(*TCCR1B, WGM13);
        break;
    case FAST_PWM_MODE_ICR1:
        CLEAR_BIT(*TCCR1A, WGM10);
        SET_BIT(*TCCR1A, WGM11);
        SET_BIT(*TCCR1B, WGM12);
        SET_BIT(*TCCR1B, WGM13);
        break;
    case FAST_PWM_MODE_OCR1A:
        SET_BIT(*TCCR1A, WGM10);
        SET_BIT(*TCCR1A, WGM11);
        SET_BIT(*TCCR1B, WGM12);
        SET_BIT(*TCCR1B, WGM13);
        break;
    }
}
static inline void _setTimer1ComA(Timer1_com_mode com_mode)
{
    switch (com_mode)
    {
    case COM_NORMAL:
        CLEAR_BIT(*TCCR1A, COM1A1);
        CLEAR_BIT(*TCCR1A, COM1A0);
        break;
    case COM_TOGGLE:
        SET_BIT(*TCCR1A, COM1A1);
        CLEAR_BIT(*TCCR1A, COM1A0);
        break;
    case COM_NON_INVERTING:
        CLEAR_BIT(*TCCR1A, COM1A1);
        SET_BIT(*TCCR1A, COM1A0);
        break;
    case COM_INVERTING:
        SET_BIT(*TCCR1A, COM1A1);
        SET_BIT(*TCCR1A, COM1A0);
        break;
    }
}
static inline void _setTimer1ComB(Timer1_com_mode com_mode)
{
    switch (com_mode)
    {
    case COM_NORMAL:
        CLEAR_BIT(*TCCR1A, COM1B1);
        CLEAR_BIT(*TCCR1A, COM1B0);
        break;
    case COM_TOGGLE:
        SET_BIT(*TCCR1A, COM1B1);
        CLEAR_BIT(*TCCR1A, COM1B0);
        break;
    case COM_NON_INVERTING:
        CLEAR_BIT(*TCCR1A, COM1B1);
        SET_BIT(*TCCR1A, COM1B0);
        break;
    case COM_INVERTING:
        SET_BIT(*TCCR1A, COM1B1);
        SET_BIT(*TCCR1A, COM1B0);
        break;
    }
}
static inline void _setTimer1Clk(Timer1_timer_clk timer_clk)
{
    switch (timer_clk)
    {
    case CLK_NO_CLK:
        CLEAR_BIT(*TCCR1B, CS10);
        CLEAR_BIT(*TCCR1B, CS11);
        CLEAR_BIT(*TCCR1B, CS12);
        break;
    case CLK_F_CPU:
        SET_BIT(*TCCR1B, CS10);
        CLEAR_BIT(*TCCR1B, CS11);
        CLEAR_BIT(*TCCR1B, CS12);
        break;
    case CLK_F_CPU_8:
        CLEAR_BIT(*TCCR1B, CS10);
        SET_BIT(*TCCR1B, CS11);
        CLEAR_BIT(*TCCR1B, CS12);
        break;
    case CLK_F_CPU_64:
        SET_BIT(*TCCR1B, CS10);
        SET_BIT(*TCCR1B, CS11);
        CLEAR_BIT(*TCCR1B, CS12);
        break;
    case CLK_F_CPU_256:
        CLEAR_BIT(*TCCR1B, CS10);
        CLEAR_BIT(*TCCR1B, CS11);
        SET_BIT(*TCCR1B, CS12);
        break;
    case CLK_F_CPU_1024:
        SET_BIT(*TCCR1B, CS10);
        CLEAR_BIT(*TCCR1B, CS11);
        SET_BIT(*TCCR1B, CS12);
        break;
    }
}
static inline void _setTimer1ICU(u8 noise_cancelling, Timer1_ICU_trigger_edge edge_behaviour)
{
    switch (edge_behaviour)
    {
    case RISING_EDGE:
        SET_BIT(*TCCR1B, ICES1);
        break;
    case FALLING_EDGE:
        CLEAR_BIT(*TCCR1B, ICES1);
        break;
    }
    switch (noise_cancelling)
    {
    case 0:
        CLEAR_BIT(*TCCR1B, ICNC1);
        break;
    default:
        SET_BIT(*TCCR1B, ICNC1);
        break;
    }
}
static inline void _setTimer1Interrupt(Timer1_timer_mode timer_mode, u16 ocra, u16 ocrb)
{
    switch (timer_mode)
    {
    case NORMAL_MODE:
        SET_BIT(*TIMSK1, TOIE1);
        break;
    case ICU_MODE:
        SET_BIT(*TIMSK1, ICIE1);
        break;
    default:
        if (ocra)
            SET_BIT(*TIMSK1, OCIE1A);
        if (ocrb)
            SET_BIT(*TIMSK1, OCIE1B);
        break;
    }
}

void Timer1_init(Timer1_config *config_ptr)
{
    *TCNT1 = config_ptr->initial_val;
    *ICR1 = config_ptr->icr1_val;
    *OCR1A = config_ptr->ocra_val;
    *OCR1B = config_ptr->ocrb_val;
    _setTimer1Clk(config_ptr->timer_clk);
    _setTimer1ComA(config_ptr->timer_com_mode_a);
    _setTimer1ComB(config_ptr->timer_com_mode_b);
    _setTimer1Mode(config_ptr->timer_mode);
    _setTimer1ICU(config_ptr->ICU_enable_noise_cancelling, config_ptr->ICU_edge_behaviour);
    if (config_ptr->timer_operation == INTERRUPT)
        _setTimer1Interrupt(config_ptr->timer_mode, config_ptr->ocra_val, config_ptr->ocrb_val);
}
void Timer1_setCallBack(volatile void (*callback_func)(void))
{
    callback_ptr = callback_func;
}

void Timer1_reset()
{
    *TCCR1B = *TCCR1A = *TCCR1C = *OCR1A = *OCR1B = *ICR1 = *TCNT1 = 0;
}

void Timer1_delay_ms(u32 delay_value)
{
    Timer1_config t1;
    t1.timer_com_mode_a = COM_NORMAL;
    t1.timer_com_mode_b = COM_NORMAL;
    t1.timer_clk = CLK_F_CPU_64;
    t1.timer_mode = CTC_MODE_ICR1;
    t1.initial_val = 0;
    t1.icr1_val = 249;
    t1.ocra_val = 0;
    t1.ocrb_val = 0;
    t1.timer_operation = POLLING;
    Timer1_init(&t1);

    u32 count = 0;
    while (count < delay_value)
    {
        if (READ_BIT(*TIFR1, ICF1))
        {
            count++;
            SET_BIT(*TIFR1, ICF1);
        }
    }
}

void Timer1_delay_us(u32 delay_value)
{
    Timer1_config t1;
    t1.timer_com_mode_a = COM_NORMAL;
    t1.timer_com_mode_b = COM_NORMAL;
    t1.timer_clk = CLK_F_CPU;
    t1.timer_mode = CTC_MODE_ICR1;
    t1.initial_val = 0;
    t1.icr1_val = 15;
    t1.ocra_val = 0;
    t1.ocrb_val = 0;
    t1.timer_operation = POLLING;
    Timer1_init(&t1);

    u32 count = 0;
    while (count < delay_value)
    {
        if (READ_BIT(*TIFR1, ICF1))
        {
            count++;
            SET_BIT(*TIFR1, ICF1);
        }
    }
}

u16 Timer1_getLastEvent() {
    return *ICR1; 
}

#endif