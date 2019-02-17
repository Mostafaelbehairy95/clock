/*
 * feature.h
 *
 * Created: 2/17/2019 7:26:23 AM
 *  Author: Elbehairy
 */ 


#ifndef FEATURE_H_
#define FEATURE_H_
#define F_CPU 16000000UL

#define NotPressed(x) (x > 900 && x < 1023 ? 1:0)
#define button1(x) (x > 0 && x < 10 ? 1:0)
#define button2(x) (x > 500 && x < 600 ? 1:0)
#define button3(x) (x > 600 && x < 720 ? 1:0)
#define button4(x) (x > 750 && x < 800 ? 1:0)
#define button5(x) (x > 800 && x < 900 ? 1:0)

int pressed;

int pointerDepth(int button);
void updateScreen(int look);




#endif /* FEATURE_H_ */