#define FOSC 12000000
#define CCLK (5*FOSC)
#define PCLK (CCLK/4)
#define PREINT_VAL  (int) ((PCLK / 32768) - 1)
#define PREFRAC_VAL  (PCLK -((PREINT_VAL + 1) * 32768))

#define CPU_LPC2129 1
#define CPU_LPC2148 2

#define CPU_SEL CPU_LPC2148
