/*
 * ADC.h
 *
 * Created: 2/27/2017 9:31:20 PM
 *  Author: elbehairy
 */ 


#ifndef ADC_H_
#define ADC_H_

#define F_CPU 16000000UL

#include <avr/io.h>

void analog_Init();
int readAnalog(uint8_t pin);
void WriteAnalog(int value);




#endif /* ADC_H_ */