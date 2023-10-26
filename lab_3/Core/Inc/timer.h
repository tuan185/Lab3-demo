/*
 * timer.h
 *
 *  Created on: Oct 25, 2023
 *      Author: Admin
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_
void timerInit(int scale, int period);
void set7SEGTimer(int duration);
void setLEDBlinkTimer(int duration);
void setButtonTimer(int duration);
void timer_run();
int getTimerFlag(int flag);
void resetTimerFlag(int flag);
#endif /* INC_TIMER_H_ */
