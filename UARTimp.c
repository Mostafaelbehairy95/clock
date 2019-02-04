/*
 * UARTimp.c
 *
 * Created: 2/22/2017 7:01:45 PM
 *  Author: elbehairy
 */ 

#include "UART.h"

void uart_init(){
	UBRR0H = (baud_Rate >> 8);
	UBRR0L = baud_Rate;
	UCSR0B |=(1 << RXEN0)|(1 << TXEN0);
	UCSR0C |=(1<<USBS0)|(3<<UCSZ00);;
}

void uart_transmit(unsigned char data){
	while(!(UCSR0A & ( 1 << UDRE0)));
	UDR0 = data;
}

char uart_receive(){
	while(!(UCSR0A & ( 1 << RXC0)));
	return UDR0;
}