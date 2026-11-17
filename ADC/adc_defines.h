#define FOSC1 12000000
#define CCLK1 (FOSC1*5)
#define PCLK1 (CCLK1/4)
#define ADC_CLK 3000000

//ADCR SFRS 
#define CLK_DIV_BITS 8 //8-15
#define PDN_BIT 21
#define ADC_CONV_START_BIT 24
#define CLK_DIV_VAL ((PCLK1/ADC_CLK)-1)

//ADDR SFRS 
#define DIGITAL_DATA_BITS 6 //6-15
#define DONE_BIT 31

#define AIN0_FUNC  0x00400000
#define AIN1_FUNC   0x01000000
#define AIN2_FUNC    0x04000000
#define AIN3_FUNC    0x10000000
