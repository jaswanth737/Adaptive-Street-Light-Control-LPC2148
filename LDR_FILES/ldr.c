
#include <math.h>

#include "types.h"
#include "adc.h"
#include "ldr.h"

/*******************************************************************************
 * LDR Sensor Configuration
 ******************************************************************************/

#define VCC       3.3
#define R_FIXED   5000
#define GAMMA     0.7

/*******************************************************************************
 * Function Name : Read_ldr
 * Description   : Reads the LDR sensor through the ADC and calculates the
 *                 corresponding resistance and illumination level.
 *
 * Parameters    : lux  - Pointer to the calculated illumination value.
 *                 rldr - Pointer to the calculated LDR resistance.
 *
 * Return        : None.
 *
 * Dependencies  : ADC driver and math library.
 ******************************************************************************/
void Read_ldr(f32 *lux, f32 *rldr)
{
    u16 adc_value = 0;
    f32 adc_voltage = 0.0;

    /* Initialize the ADC peripheral. */
    adc_init();

    /* Acquire the ADC conversion result and corresponding input voltage. */
    Read_ADC(1, &adc_value, &adc_voltage);

    /* Calculate LDR resistance using the voltage-divider equation. */
    *rldr = (R_FIXED * adc_voltage) / (VCC - adc_voltage);

    /* Calculate illumination level using the empirical power-law model. */
    *lux = 10.0 * pow(12000.0 / (*rldr), 1.0 / GAMMA);
}
