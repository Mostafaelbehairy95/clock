/*
 * ADCimp.c
 *
 * Created: 2/27/2017 9:31:35 PM
 *  Author: elbehairy
 */ 

#include "ADC.h"

void analog_Init(){
	ADCSRA |= (1 << ADEN) | (1 << ADPS2)| (1 << ADPS1)| (1 << ADPS0);
	ADMUX  |= (1 << REFS0);
}

int readAnalog(uint8_t pin){
	ADMUX |= (pin & 0b00000111);
	ADCSRA |= (1 << ADSC);
	while(ADCSRA & (1<<ADSC));
	ADCSRA|=(1<<ADIF);
	return(ADC); 
}