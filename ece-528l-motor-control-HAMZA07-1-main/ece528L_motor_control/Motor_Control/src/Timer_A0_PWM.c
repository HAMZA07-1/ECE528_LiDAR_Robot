#include "../inc/Timer_A0_PWM.h"

void Timer_A0_PWM_Init(uint16_t period_constant, uint16_t duty_cycle_1, uint16_t duty_cycle_2)
{
    if (duty_cycle_1 >= period_constant) return;
    if (duty_cycle_2 >= period_constant) return;

    // P2.6 = TA0.3, P2.7 = TA0.4
    P2->SEL0 |= 0xC0;
    P2->SEL1 &= ~0xC0;
    P2->DIR  |= 0xC0;

    // Set PWM period
    TIMER_A0->CCR[0] = period_constant;

    // Divide by 1 in expansion register
    TIMER_A0->EX0 = 0x0000;

    // Toggle / Reset mode
    TIMER_A0->CCTL[3] = 0x0040;
    TIMER_A0->CCR[3] = duty_cycle_1;

    TIMER_A0->CCTL[4] = 0x0040;
    TIMER_A0->CCR[4] = duty_cycle_2;

    // SMCLK, divide by 8, Up/Down mode, clear timer
    TIMER_A0->CTL = 0x0274;
}

void Timer_A0_Update_Duty_Cycle_1(uint16_t duty_cycle_1)
{
    if (duty_cycle_1 >= TIMER_A0->CCR[0]) return;
    TIMER_A0->CCR[3] = duty_cycle_1;
}

void Timer_A0_Update_Duty_Cycle_2(uint16_t duty_cycle_2)
{
    if (duty_cycle_2 >= TIMER_A0->CCR[0]) return;
    TIMER_A0->CCR[4] = duty_cycle_2;
}
