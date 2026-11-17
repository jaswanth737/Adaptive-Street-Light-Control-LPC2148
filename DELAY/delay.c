
/*******************************************************************************
 * File Name : delay.c
 * Description : Software Delay Driver Implementation for LPC21xx.
 *               Provides blocking software delay functions for generating
 *               microsecond, millisecond and second-level delays.
 *
 * Dependencies : System clock configuration and delay driver definitions.
 ******************************************************************************/

#include "types.h"
#include "delay.h"

/*******************************************************************************
 * Function Name : delay_us
 * Description   : Generates a software-based delay in microseconds.
 *
 *                 Uses a calibrated decrement loop to consume processor
 *                 clock cycles corresponding to the requested delay.
 *
 * Parameters    : dlyUS - Required delay duration in microseconds.
 * Return        : void.
 *
 * Notes         : Delay calibration factor is based on approximately
 *                 12 loop iterations per microsecond.
 ******************************************************************************/
void delay_us(u32 dlyUS)
{
    // Scale the requested microsecond delay using the calibration factor.
    dlyUS *= 12;

    // Execute the decrement loop to generate the required delay.
    while(dlyUS--);

    // Approximate loop execution time: 5 processor clock cycles.
    // Estimated total cycles = 12 * 5 = 60 clock cycles per microsecond.
}

/*******************************************************************************
 * Function Name : delay_ms
 * Description   : Generates a software-based delay in milliseconds.
 *
 *                 Converts the requested millisecond duration into
 *                 equivalent loop iterations and executes a blocking
 *                 decrement loop.
 *
 * Parameters    : dlyMS - Required delay duration in milliseconds.
 * Return        : void.
 *
 * Notes         : Delay calibration factor is based on approximately
 *                 12000 loop iterations per millisecond.
 ******************************************************************************/
void delay_ms(u32 dlyMS)
{
    // Scale the requested millisecond delay using the calibration factor.
    dlyMS *= 12000;

    // Execute the decrement loop to generate the required delay.
    while(dlyMS--);

    // Approximate loop execution time: 5 processor clock cycles.
    // Estimated total cycles = 12000 * 5 = 60000 clock cycles per millisecond.
}

/*******************************************************************************
 * Function Name : delay_s
 * Description   : Generates a software-based delay in seconds.
 *
 *                 Converts the requested second duration into
 *                 equivalent loop iterations and executes a blocking
 *                 decrement loop.
 *
 * Parameters    : dlyS - Required delay duration in seconds.
 * Return        : void.
 *
 * Notes         : Delay calibration factor is based on approximately
 *                 12000000 loop iterations per second.
 ******************************************************************************/
void delay_s(u32 dlyS)
{
    // Scale the requested second delay using the calibration factor.
    dlyS *= 12000000;

    // Execute the decrement loop to generate the required delay.
    while(dlyS--);

    // Approximate loop execution time: 5 processor clock cycles.
    // Estimated total cycles = 12000000 * 5 = 60000000 clock cycles per second.
}
