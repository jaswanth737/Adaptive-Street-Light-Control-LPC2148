//eint.h
void eint0_init(void);
void eint0_isr(void) __irq;
extern volatile unsigned int ext_flag;
