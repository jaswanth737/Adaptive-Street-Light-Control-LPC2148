#include <LPC21xx.H>
#include "rtc_alarm_interrupt.h"
#include "rtc_alarm_interrupt_defines.h"
#include "rtc.h"
#include "rtc_defines.h"
volatile unsigned char LED_IS_ON=0;
void rtc_isr(void) __irq{
	ILR=1<<1;
	if(HOUR == 18 && MIN == 00 && SEC == 00){
	ALSEC=00;
	ALMIN=00;
	ALHOUR=6;
	LED_IS_ON=1;
}
	else{
	LED_IS_ON=0;
	ALSEC=00;
	ALMIN=00;
	ALHOUR=18;
	}
	//clear status of eint0 in VIC
	VICVectAddr=0;
}
	void RTC_alarm_interrupt_init(){
   VICIntSelect=0; //default its 0
	
	//cfg eint0 as vectored IRQ priority 0
	VICVectCntl1=(1<<5)|13;
	//load eint0_isr address
	VICVectAddr1=(unsigned)rtc_isr;
	//enabe eint0 in VIC
	VICIntEnable=1<<13;
	AMR=0XF8;
	ALSEC=00;
	ALMIN=00;
	ALHOUR=18;
	}
