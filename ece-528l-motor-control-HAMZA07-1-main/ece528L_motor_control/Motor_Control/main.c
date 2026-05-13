#include "msp.h"
#include "inc/Clock.h"
#include "inc/Motor.h"

char cmd;

static void UART2_Init_9600(void)
{
    P3->SEL0 |= (BIT2 | BIT3);
    P3->SEL1 &= ~(BIT2 | BIT3);

    EUSCI_A2->CTLW0 |= 0x0001;
    EUSCI_A2->CTLW0 = 0x0081;
    EUSCI_A2->BRW = 1250;
    EUSCI_A2->MCTLW = 0;
    EUSCI_A2->CTLW0 &= ~0x0001;
}

static char UART2_InChar(void)
{
    while ((EUSCI_A2->IFG & 0x01) == 0)
    {
    }
    return (char)EUSCI_A2->RXBUF;
}

int main(void)
{
    Clock_Init48MHz();
    Motor_Init();

    P1->DIR  |= BIT0;
    P1->OUT  &= ~BIT0;

    UART2_Init_9600();

    while (1)
    {
        cmd = UART2_InChar();

        if (cmd == 'F')
        {
            P1->OUT |= BIT0;
            Motor_Forward(8500, 8500);
            Clock_Delay1ms(300);
            Motor_Stop();
        }
        else if (cmd == 'L')
        {
            P1->OUT |= BIT0;
            Motor_Left(7500, 7500);
            Clock_Delay1ms(350);
            Motor_Stop();
        }
        else if (cmd == 'R')
        {
            P1->OUT |= BIT0;
            Motor_Right(7500, 7500);
            Clock_Delay1ms(350);
            Motor_Stop();
        }
        else if (cmd == 'B')
        {
            P1->OUT |= BIT0;
            Motor_Backward(7500, 7500);
            Clock_Delay1ms(300);
            Motor_Stop();
        }
        else if (cmd == 'U')
        {
            P1->OUT |= BIT0;
            Motor_Left(8000, 8000);
            Clock_Delay1ms(900);
            Motor_Stop();
        }
        else if (cmd == 'S')
        {
            P1->OUT &= ~BIT0;
            Motor_Stop();
        }
    }
}
