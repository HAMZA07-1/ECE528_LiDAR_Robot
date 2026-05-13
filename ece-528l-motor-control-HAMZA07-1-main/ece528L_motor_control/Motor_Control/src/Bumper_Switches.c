/**
 * @file Bumper_Switches.c
 * @brief Source code for the Bumper_Switches driver.
 *
 * This file contains the function definitions for the Bumper_Switches driver.
 * It is used to demonstrate external I/O-triggered interrupts.
 * The driver interfaces with the following:
 *  - Pololu Left Bumper Switches
 *  - Pololu Right Bumper Switches
 *
 * The following pins are used when the Bumper Switches are connected to the TI MSP432 LaunchPad:
 *  - BUMP_0                    <-->    MSP432 LaunchPad Pin P4.0
 *  - BUMP_1                    <-->    MSP432 LaunchPad Pin P4.2
 *  - BUMP_2                    <-->    MSP432 LaunchPad Pin P4.3
 *  - Right Bumper Switch GND   <-->    MSP432 LaunchPad GND
 *  - BUMP_3                    <-->    MSP432 LaunchPad Pin P4.5
 *  - BUMP_4                    <-->    MSP432 LaunchPad Pin P4.6
 *  - BUMP_5                    <-->    MSP432 LaunchPad Pin P4.7
 *  - Left Bumper Switch GND    <-->    MSP432 LaunchPad GND
 *
 * @note The Bumper Switches operate in an active low configuration.
 * When the switches are pressed, they connect to GND.
 *
 * @author Aaron Nanas
 */

#include "../inc/Bumper_Switches.h"

void Bumper_Switches_Init(void(*task)(uint8_t))
{
    // Store the user-defined task function for use during interrupt handling
    Bumper_Task = task;

    // Configure P4.7, P4.6, P4.5, P4.3, P4.2, and P4.0 as GPIO pins
    P4->SEL0 &= ~0xED;
    P4->SEL1 &= ~0xED;

    // Configure the pins as inputs
    P4->DIR &= ~0xED;

    // Enable pull resistors and configure them as pull-up resistors
    P4->REN |= 0xED;
    P4->OUT |= 0xED;

    // Configure falling-edge interrupt triggers
    P4->IES |= 0xED;

    // Clear any existing interrupt flags
    P4->IFG &= ~0xED;

    // Enable interrupts on bumper pins
    P4->IE |= 0xED;

    // Set IRQ 38 (PORT4) priority to 0
    NVIC->IP[9] &= ~0x00E00000;

    // Enable IRQ 38 in NVIC (bit 6 of ISER1)
    NVIC->ISER[1] |= 0x00000040;
}

uint8_t Bumper_Read(void)
{
    uint32_t bumper_state = ~P4->IN;
    return (((bumper_state & 0xE0) >> 2) |
            ((bumper_state & 0x0C) >> 1) |
            (bumper_state & 0x01));
}

/**
 * @brief Interrupt handler for PORT4 (P4) events.
 *
 * This function is an interrupt service routine (ISR) for PORT4 of the TI MSP432 LaunchPad.
 * It is triggered on a falling edge event on any of the bumper switch pins.
 *
 * @return None
 */
void PORT4_IRQHandler(void)
{
    // Clear interrupt flags for bumper pins
    P4->IFG &= ~0xED;

    // Execute the user-defined task
    (*Bumper_Task)(Bumper_Read());
}
