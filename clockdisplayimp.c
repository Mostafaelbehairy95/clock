/*
 * clockdisplayimp.c
 *
 * Created: 11/2/2016 9:02:14 AM
 *  Author: elbehairy
 */ 


#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <math.h>
#include "clockdisplay.h"

 
 int numberOfSegement[13] = {0x3f,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x38,0x3e,0x79};


void _7Segment_Init(){
	DDRD_7segment |= mask_7segmentD;
	DDRC_7segment |= (1 << bit0);
	DDRC_7segment |= (1 << bit1);
	DDRC_7segment |= (1 << bit2);
	DDRD_7segment |= (1 << bit3);
	
}



void shiftRegister7segment(int data){
seven_segementD &= ~(1 << S_CLK);
seven_segementD &= ~(1 << R_CLK);
	for(int i = 7; i >= 0; i --){
			if( numberOfSegement[data]& (1 << i)){
				seven_segementD |= (1 << SER);
			}else{
				seven_segementD &= ~(1 << SER);	
			}

		seven_segementD |= (1 << S_CLK);	
		seven_segementD &= ~(1 << S_CLK);					
	}
	seven_segementD |= (1 << R_CLK);
}

void setClock(int hr, int min){
	for (int i = 0; i < 4; i++)
	{
		shiftRegister7segment((hr/10)%10);
		PORTC &= ~(1<<PORTC0);
		PORTD |= (1<<PORTD4);
		_delay_ms(4);
		
		shiftRegister7segment(hr%10);
		PORTD &= ~(1<<PORTD4);
		PORTC |= (1<<PORTC2);
		_delay_ms(4);

		shiftRegister7segment((min/10)%10);
		PORTC &= ~(1<<PORTC2);
		PORTC |= (1<<PORTC1);
		_delay_ms(4);

		shiftRegister7segment(min%10);
		PORTC &= ~(1<<PORTC1);
		PORTC |= (1<<PORTC0);
		_delay_ms(5);

					
	}

}
