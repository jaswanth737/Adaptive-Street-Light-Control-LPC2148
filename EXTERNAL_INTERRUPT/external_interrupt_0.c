
/*******************************************************************************
 * File Name : external_interrupt_0.c
 * Description : External Interrupt 0 driver implementation for LPC21xx.
 *               Configures EINT0 through the PINSEL and VIC peripherals
 *               and handles external interrupt events using an IRQ ISR.
 ******************************************************************************/

#include <LPC21xx.h>

#include "types.h"
#include "eint.h"
#include "delay.h"
#include "eint_defines.h"
#include "lcd.h"
#include "lcd_defines.h"
#include "kpm.h"
#include "kpm_defines.h"
#include "RTC_edit.h"
#include "time_edit.h"

/*******************************************************************************
 * Global Variable Declaration
 ******************************************************************************/

/*
 * Variable Name : ext_flag
 * Description   : Indicates the occurrence of an External Interrupt 0 event.
 *                 Set by the EINT0 ISR and monitored by the main application
 *                 to initiate the RTC and street light timing configuration.
 * Data Type     : volatile unsigned int.
 * Initial Value : 0.
 * Note          : Volatile ensures that the compiler does not optimize away
 *                 accesses to this variable shared between ISR and main code.
 */
volatile unsigned int ext_flag = 0;

/*******************************************************************************
 * Function Name : eint0_init
 * Description   : Initializes External Interrupt 0 (EINT0) of the LPC21xx.
 *
 *                 Configures the P0.1 pin for EINT0 functionality,
 *                 assigns the interrupt to a vectored IRQ slot in the VIC,
 *                 enables the interrupt source and configures EINT0
 *                 for falling-edge-triggered operation.
 *
 *                 Configuration Sequence:
 *                 1. Configure P0.1 as EINT0 using PINSEL0.
 *                 2. Configure the VIC interrupt type as IRQ.
 *                 3. Assign EINT0 to VIC vectored interrupt slot 0.
 *                 4. Register the EINT0 ISR address.
 *                 5. Enable EINT0 in the VIC.
 *                 6. Configure EINT0 as edge-triggered.
 *
 * Parameters    : None.
 * Return        : void.
 * Dependencies  : VIC, PINSEL0 and External Interrupt peripherals.
 ******************************************************************************/
void eint0_init(void)
{
    // Configure P0.1 as the EINT0 external interrupt input pin.
    PINSEL0 &= ~(3 << (1 * 2));
    PINSEL0 |= EINT0_PIN_FUNC;

    /***************************************************************************
     * VIC Configuration
     **************************************************************************/

    // Configure all VIC interrupt sources as IRQ interrupts.
    // VICIntSelect = 0 selects IRQ operation for all interrupt sources.
    VICIntSelect = 0;

    // Configure VIC vectored interrupt slot 0 for EINT0.
    // Bit 5 enables the vectored interrupt slot.
    // EINT0_VIC_CHN0 specifies the EINT0 interrupt channel number.
    VICVectCntl0 = (1 << 5) | EINT0_VIC_CHN0;

    // Load the EINT0 ISR address into VIC vectored address register 0.
    VICVectAddr0 = (unsigned)eint0_isr;

    // Enable the EINT0 interrupt source in the VIC.
    VICIntEnable = 1 << EINT0_VIC_CHN0;

    /***************************************************************************
     * External Interrupt Peripheral Configuration
     **************************************************************************/

    // Configure EINT0 for edge-triggered interrupt operation.
    // Setting bit 0 selects edge-sensitive triggering.
    EXTMODE = 1 << 0;

    // EXTPOLAR bit 0 = 0 selects falling-edge triggering.
    // Falling-edge operation is selected by default.
    // EXTPOLAR = 0;

    // EXTINT bit 0 can be used to clear the pending EINT0 interrupt flag.
    // EXTINT = 0;
}

/*******************************************************************************
 * Function Name : eint0_isr
 * Description   : External Interrupt 0 Interrupt Service Routine.
 *
 *                 Executes when a falling edge is detected on the EINT0 pin.
 *                 Sets the application event flag to notify the main
 *                 application that an external interrupt has occurred.
 *
 *                 Clears the pending interrupt status in the External
 *                 Interrupt peripheral and signals completion of the
 *                 interrupt service to the VIC.
 *
 * Parameters    : None.
 * Return        : void.
 * Interrupt     : External Interrupt 0 (EINT0), IRQ.
 *
 * ISR Operations:
 *                 1. Set the external interrupt event flag.
 *                 2. Clear the EINT0 interrupt status.
 *                 3. Signal end of interrupt processing to the VIC.
 ******************************************************************************/
void eint0_isr(void) __irq
{
    // Set the event flag to notify the main application of EINT0 occurrence.
    ext_flag = 1;

    // Clear the pending EINT0 interrupt flag in the EXTINT register.
    // Writing a logic HIGH to bit 0 clears the corresponding interrupt flag.
    EXTINT = 1 << 0;

    // Signal end of interrupt processing to the VIC.
    // Writing zero indicates completion of the current vectored IRQ.
    VICVectAddr = 0;
}
