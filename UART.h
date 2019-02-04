/*
 * UART.h
 *
 * Created: 2/22/2017 7:01:29 PM
 *  Author: elbehairy
 */ 
#define F_CPU 16000000UL

#define baud 9600
#define baud_Rate (F_CPU/(16UL*baud)-1)

#ifndef UART_H_
#define UART_H_
#include <avr/io.h>

void uart_init();

void uart_transmit(unsigned char data);
void printstr(unsigned char * str);
void printInt(int integer);

unsigned  char uart_receive();


#endif /* UART_H_ */