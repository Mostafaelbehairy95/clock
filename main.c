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
#include "UART.h"

// Menu Words
char PagesChoose [6][12] = {"1-SetClock","2-SetData","3-SetAlarm","4-StopWatch","5-Pomodoro","6-24/12Mode"};
char weekDay[7][4] = {"Sat","Sun","Mon","Tue","Wed","thu","Fri"};
char PageTime[3][8] = {"Hour:","Minute:","Second:"};
char PageDate[4][9] = {"Day:","Month:","Year:","WeekDay:"};
//??????????????????????????????????????????????????????????????????????????????

//Global Variable
RTC t;
int button,pointer = 0;
bool pressed = 0;

//??????????????????????????????????????????????????????????????????????????????

//Function
void updateTime(int hour,int minute);
void updateDate(int day,int month, int year, int weekDay);
void updateScreen(int n);
//??????????????????????????????????????????????????????????????????????????????
	
int main(void)
{	// initialization
	lcd4Bit_Init();
	RTC_Init();
	_7Segment_Init();
	uart_init();
	analog_Init();
	//?????????????????????????????????????????????????????????????????????????
	////Set time
	//t.hour = 7; 
	//t.min = 47;
	//t.sec = 0;
	//t.date = 15;
	//t.month = 2;
	//t.year = 19;
	//t.Mode12_24 = 1;
	//t.AmPm = 1;
	//RTC_WriteDataTime(&t);
	//?????????????????????????????????????????????????????????????????????????
	RTC_ReadDataTime(&t);
	lcd4bitInt(t.date);
	lcd4Bitdata('/');
	lcd4bitInt(t.month);
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
			lcd4bitInt(t.date);
			lcd4Bitdata('/');
			lcd4bitInt(t.month);
			lcd4Bitdata('/');
			lcd4bitInt(t.year + 2000);	
			lcd4BitIns(LINE_ONE + 14);
			lcd4BitStr("AM");			
		}
		//Menu Button Contoll
		button = readAnalog(3);
		if(button >= 0 && button < 10){
			updateScreen(pointer);
			while(1){
				RTC_ReadDataTime(&t);
				for(int i = 0; i < 5; i ++){
					setClock(t.hour,t.min);
				}				
				button = readAnalog(3);
				if(button > 900 && button <= 1023){
					pressed = 0;
				}else if(button > 500 && button < 600 && !pressed){ // up
					pointer -- ;
					if(pointer > -6){	
						updateScreen(pointer);
					}else{
						updateScreen(pointer);
						pointer = 0;
					}											
					pressed = 1;
				}else if(button > 600 && button < 720 && !pressed){// down
					pointer ++;
					if(pointer <= 5){
						updateScreen(pointer);
					}else{
						pointer = 0;
						updateScreen(pointer);
						
					}											
					pressed = 1;
				}else if(button > 750 && button < 800 && !pressed){// enter
					pressed = 1;
				}else if(button > 800 && button < 900 && !pressed){// back
					pressed = 1;
					lcd4BitIns(LCD_CLEAR);
					_delay_ms(10);
					lcd4bitInt(t.date);
					lcd4Bitdata('/');
					lcd4bitInt(t.month);
					lcd4Bitdata('/');
					lcd4bitInt(t.year + 2000);
					if(t.AmPm && t.Mode12_24){
						lcd4BitIns(LINE_ONE +14);
						lcd4BitStr("PM");
					}else if(!t.AmPm && t.Mode12_24){
						lcd4BitIns(LINE_ONE +14);	
						lcd4BitStr("AM");
					}
					break;
				}		
			}
		}
	}
}

void updateScreen(int n){
	n = (n + 6) % 6;
	if(n < 5){
				
		lcd4BitIns(LCD_CLEAR);
		_delay_ms(10);		
		lcd4BitIns(LINE_ONE);
		lcd4BitStr(PagesChoose[n]);
		
		lcd4BitIns(LINE_ONE + 14);
		lcd4bitInt(pointer);
		
		LCD_build(0,LeftArrow);
		LCD_DisplayChar(0,LINE_ONE + 13);
		lcd4BitIns(LINE_TWO);
		lcd4BitStr(PagesChoose[n + 1]);
	}else if(n == 5){
		
		lcd4BitIns(LCD_CLEAR);	
		_delay_ms(10);	
		lcd4BitIns(LINE_ONE);
		lcd4BitStr(PagesChoose[n]);
		
		lcd4BitIns(LINE_ONE + 14);
		lcd4bitInt(pointer);

		LCD_build(0,LeftArrow);
		LCD_DisplayChar(0,LINE_ONE + 13);

		
	}
}	
		