/*
 * main.c
 *
 * Created: 11/2/2016 8:59:32 AM
 *  Author: elbehairy
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <math.h>


#include "clockdisplay.h"
#include "lcd.h"
#include "RTC.h"
#include "ADC.h"

//Macro Definition
#define DArrow 1
#define UArrow 2
#define LArrow 3
#define Battery 4
//??????????????????????????????????????????????????????????????????????????????


// Variable
int listenButton = 0;
int list = 0,hms = 0;
RTC t;
int read;
//??????????????????????????????????????????????????????????????????????????????

// Menu Words
char PagesChoose [8][12] = {"1-SetClock","2-SetData","3-SetAlarm","4-countDow+n","5-StopWatch","6-24Mode","7-AM/PM","8-Exit"};
char PagesTime[3][8] = {"Hour:","Minute:","Second:"};
//??????????????????????????????????????????????????????????????????????????????
	


// Function
int convertFromTo(double value, double fromst, double fromend, double tost, double toend);
void updateTime();
void updateData();
//??????????????????????????????????????????????????????????????????????????????


int main(void)
{	
	// initialization
	lcd4Bit_Init();
	RTC_Init();
	_7Segment_Init();
	//?????????????????????????????????????????????????????????????????????????
	////Set time
	//t.hour = 11; 
	//t.min = 17;
	//t.sec = 00;
	//t.date = 4;
	//t.month = 2;
	//t.year = 19;
	//t.Mode12_24 = 1;
	//t.AmPm = 1;
	//RTC_WriteDataTime(&t);
	//////?????????????????????????????????????????????????????????????????????????
	RTC_ReadDataTime(&t);
	lcd4bitInt(t.month);
	lcd4Bitdata('/');
	lcd4bitInt(t.date);
	lcd4Bitdata('/');
	lcd4bitInt(t.year + 2000);
	if(t.AmPm && t.Mode12_24){
		lcd4BitIns(LINE_ONE +14);
		lcd4BitStr("PM");
	}else if(!t.AmPm && t.Mode12_24){
		lcd4BitIns(LINE_ONE +14);	
		lcd4BitStr("AM");
	}

	while(1){
		RTC_ReadDataTime(&t);		
		setClock(t.hour,t.min);
		if(t.AmPm && t.Mode12_24 && t.hour == 12 && t.sec < 50 && t.min < 1){
			lcd4BitIns(LINE_ONE + 14);
			lcd4BitStr("PM");
		}else if(!t.AmPm && t.Mode12_24 && t.hour == 12 && t.sec < 2 && t.min < 1){
			lcd4BitIns(LINE_ONE );
			lcd4bitInt(t.month);
			lcd4Bitdata('/');
			lcd4bitInt(t.date);
			lcd4Bitdata('/');
			lcd4bitInt(t.year + 2000);	
			lcd4BitIns(LINE_ONE + 14);
			lcd4BitStr("AM");
		}
	}

}

int convertFromTo(double value, double fromst, double fromend, double tost, double toend){
	 double result;
	 fromend -= fromst;
	 toend -= tost;
	 result = (((value * toend)/fromend) + tost);
	 return (int)round(result);
}

void updateTime(){
	do{
		read = convertFromTo(readAnalog(2),0,1023,0,9);
		if(read == 0){
			hms ++;
			hms %= 3;
			if(hms == 0 || hms == 1){
				lcd4BitIns(LCD_CLEAR);
				_delay_ms(4);
				lcd4BitIns(LINE_ONE);
				lcd4BitStr(PagesTime[0]);
				lcd4BitIns(LINE_TWO);
				lcd4BitStr(PagesTime[1]);
			}else{
				lcd4BitIns(LCD_CLEAR);
				_delay_ms(4);
				lcd4BitIns(LINE_ONE);
				lcd4BitStr(PagesTime[2]);				
			}
			if(hms % 2 == 0){
				LCD_DisplayChar(LArrow, LINE_ONE + 13);
				lcd4BitIns(LINE_TWO + 10);
				lcd4Bitdata(' ');									
			}else{
				LCD_DisplayChar(LArrow, LINE_TWO + 13);
				lcd4BitIns(LINE_ONE + 13);
				lcd4Bitdata(' ');													
			}
		}else if(read == 5){ // Increase Hour,Minute and Second
			if(hms == 0){
				t.hour += 1;
				t.hour %= 12;
				if(t.hour == 0){
					t.hour = 1;
				}
				lcd4BitIns(LINE_ONE + 7);
				lcd4bitInt(t.hour);
			}else if(hms == 1){
				t.min += 1;
				t.min %= 59;
				lcd4BitIns(LINE_TWO + 7);
				lcd4bitInt(t.min);
				
			}else if(hms == 2){
				t.sec += 1;
				t.sec %= 59;
				lcd4BitIns(LINE_ONE + 7);
				lcd4bitInt(t.sec);		
			}
		}else if(read == 6){ // Decrease Hour, minute and second
			if(hms == 0){
				t.hour -= 1;
				t.hour %= 12;
				if(t.hour == 0){
					t.hour = 1;
				}
				lcd4BitIns(LINE_ONE + 7);
				lcd4bitInt(t.hour);
			}else if(hms == 1){
				t.min -= 1;
				t.min %= 59;
				lcd4BitIns(LINE_TWO + 7);
				lcd4bitInt(t.min);
				
			}else if(hms == 2){
				t.sec -= 1;
				t.sec %= 59;
				lcd4BitIns(LINE_ONE + 7);
				lcd4bitInt(t.sec);		
			}
			
		}	
		_delay_ms(150);			
	}while(read != 7);
}

void updateData(){
	
}