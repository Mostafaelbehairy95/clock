/*
 * featureimp.c
 *
 * Created: 2/17/2019 7:26:36 AM
 *  Author: Elbehairy
 */ 

#include <avr/io.h>
#include "feature.h"
#include "lcd.h"

int pressed = 0;
// Menu Words
char PagesChoose [6][12] = {"1-SetClock","2-SetData","3-SetAlarm","4-StopWatch","5-Pomodoro","6-24/12Mode"};
char weekDay[7][4] = {"Sat","Sun","Mon","Tue","Wed","thu","Fri"};
char PageTime[3][8] = {"Hour:","Minute:","Second:"};
char PageDate[4][9] = {"Day:","Month:","Year:","WeekDay:"};
//??????????????????????????????????????????????????????????????????????????????

int pointerDepth(int button){
	int look;
	if(NotPressed(button)){
		pressed = 0;
	}else if(button2(button) && !pressed){ // up
		look -- ;
		if(look > -6){	
			updateScreen(look);
		}else{
			updateScreen(look);
			look = 0;
		}											
		pressed = 1;
	}else if(button3(button)&& !pressed){// down
		look ++;
		if(look <= 5){
			updateScreen(look);
		}else{
			look = 0;
			updateScreen(look);				
		}											
		pressed = 1;
	}else if(button4(button) && !pressed){// enter
		pressed = 1;
	}else if(button5(button) && !pressed){// back
		pressed = 1;
	}		
	return look;		
}

void updateScreen(int look){
	look = (look + 6) % 6;
	if(look < 5){
				
		lcd4BitIns(LCD_CLEAR);
		_delay_ms(10);		
		lcd4BitIns(LINE_ONE);
		lcd4BitStr(PagesChoose[look]);
		
		
		LCD_build(0,LeftArrow);
		LCD_DisplayChar(0,LINE_ONE + 13);
		lcd4BitIns(LINE_TWO);
		lcd4BitStr(PagesChoose[look + 1]);
	}else if(look == 5){
		
		lcd4BitIns(LCD_CLEAR);	
		_delay_ms(10);	
		lcd4BitIns(LINE_ONE);
		lcd4BitStr(PagesChoose[look]);
		

		LCD_build(0,LeftArrow);
		LCD_DisplayChar(0,LINE_ONE + 13);

		
	}	
}
