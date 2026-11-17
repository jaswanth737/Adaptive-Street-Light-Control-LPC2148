
int main(){
	PINSEL1|=0x00400000;
	ADCR|=(1<<PDN_BIT)|(CLK_DIV_VAL<<CLK_DIV_BITS);
	
	
	
	
	
}