/*
 * clockdisplay.h
 *
 * Created: 11/2/2016 9:00:46 AM
 *  Author: elbehairy
 */ 


#ifndef CLOCKDISPLAY_H_
#define CLOCKDISPLAY_H_


#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#define bit0 PORTC0
#define bit1 PORTC1
#define bit2 PORTC2
#define bit3 PORTD4
#define SER	PORTD5
#define S_CLK PORTD6
#define R_CLK PORTD7
#define seven_segementD PORTD
#define DDRD_7segment DDRD
#define DDRC_7segment DDRC
#define mask_7segmentD 0xe0




int time,hour,minute,second;
//int numberOfSegement[13];
//numberOfSegement[0] = 0x3f;  // 0 = 00111111 ==> F,E,D,C,B,A
//numberOfSegement[1] = 0x06;  // 1 = 00000110 ==> C,B
//numberOfSegement[2] = 0x5B;  // 2 = 01011011 ==> G,E,D,B,A
//numberOfSegement[3] = 0x4F;  // 3 = 01001111 ==> G,D,C,B,A
//numberOfSegement[4] = 0x66;  // 4 = 01100110 ==> G,F,C,B
//numberOfSegement[5] = 0x6D;  // 5 = 01101101 ==> G,F,D,C,A
//numberOfSegement[6] = 0x7D;  // 6 = 01111101 ==> G,F,E,D,C,A
//numberOfSegement[7] = 0x07;  // 7 = 00000111 ==> C,B,A
//numberOfSegement[8] = 0x7F;  // 8 = 01111111 ==> G,F,E,D,C,B,A
//numberOfSegement[9] = 0x6F;  // 9 = 00111111 ==> F,E,D,C,B,A
//numberOfSegement[10] = 0x38; // L
//numberOfSegement[11] = 0x3e; // v
//numberOfSegement[12] = 0x79; // E

void _7Segment_Init();
void setClock(int hr, int min);
void updatePeriod();
void segement(char num, uint8_t in, uint8_t mask);
void shiftRegister7segment(int data);
void setColon();
char* toChar(int num);
int toInt(char* num, int sz);




#endif /* CLOCKDISPLAY_H_ */