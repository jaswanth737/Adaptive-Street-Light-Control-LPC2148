
#include <LPC21XX.H>

#include "adc_defines.h"
#include "types.h"
#include "delay.h"

/*******************************************************************************
 * Function Name : adc_init
 * Description   : Initializes the ADC peripheral of the LPC21xx microcontroller.
 *
 *                 Configures the ADC input pins through the PINSEL1 register
 *                 and enables the ADC peripheral by configuring the ADCR
 *                 register.
 *
 *                 Configuration Details:
 *                 1. Configures P0.27 and P0.28 for ADC functionality.
 *                 2. Enables the ADC peripheral using the PDN bit.
 *                 3. Configures the ADC clock using the clock divider.
 *
 * Parameters    : None.
 * Return        : void.
 * Dependencies  : ADC configuration definitions.
 ******************************************************************************/
void adc_init()
{
    // Clear the pin function selection bits corresponding to ADC input pins.
    PINSEL1 &= ~(0xFF << ((27 - 16) * 2));

    // Configure the required pins for ADC input functionality.
    PINSEL1 |= AIN0_FUNC | AIN1_FUNC;

    // Enable the ADC peripheral and configure the ADC clock divider.
    ADCR |= (1 << PDN_BIT) | (CLK_DIV_VAL << CLK_DIV_BITS);
}

/*******************************************************************************
 * Function Name : Read_ADC
 * Description   : Performs ADC conversion on the specified ADC channel
 *                 and returns the corresponding digital and analog values.
 *
 *                 Conversion Sequence:
 *                 1. Clears the previous ADC channel selection.
 *                 2. Selects the required ADC input channel.
 *                 3. Starts the ADC conversion.
 *                 4. Waits for conversion completion by monitoring
 *                    the DONE status bit.
 *                 5. Stops the ADC conversion.
 *                 6. Extracts the 10-bit digital conversion result.
 *                 7. Converts the digital result into an analog voltage.
 *
 * Parameters    : chno - ADC channel number to be selected.
 *                 dval - Pointer to store the 10-bit ADC digital result.
 *                 eAR  - Pointer to store the calculated analog input voltage.
 *
 * Return        : void.
 * Dependencies  : ADC registers and delay driver.
 ******************************************************************************/
void Read_ADC(u8 chno, u16 *dval, f32 *eAR)
{
    // Clear the previous ADC channel selection bits in the ADCR register.
    // The lower 8 bits of ADCR are used for channel selection.
    // ADCR &= ~(0xFF << 0);
    ADCR &= 0XFFFFFF00;

    // Select the required ADC channel and initiate conversion.
    ADCR |= (1 << ADC_CONV_START_BIT) | (1 << chno);

    // Provide the required ADC conversion delay.
    // ADC conversion time depends on the configured ADC clock.
    delay_us(3);

    // Wait until the ADC DONE status bit indicates conversion completion.
    while(((ADDR >> DONE_BIT) & 1) == 0);

    // Clear the ADC conversion start bits after conversion completion.
    ADCR &= ~(1 << ADC_CONV_START_BIT);

    // Extract the 10-bit ADC digital conversion result from ADDR.
    *dval |= ((ADDR >> DIGITAL_DATA_BITS) & 1023);

    // Convert the digital ADC result into its corresponding analog voltage.
    // ADC resolution = 10 bits (0 to 1023).
    // Reference voltage = 3.3 V.
    *eAR = (*dval * (3.3 / 1023));
}
