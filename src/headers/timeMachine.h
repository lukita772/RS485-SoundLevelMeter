/*
 * timeMachine.h
 *
 *  Created on: 26 de ago. de 2018
 *      Author: Luca
 */

#ifndef HEADERS_TIMEMACHINE_H_
#define HEADERS_TIMEMACHINE_H_

typedef uint32_t T_Time;
typedef uint8_t T_TimeOut;

typedef struct
{
	T_Time time;
	void(*func_p)(void);
	T_TimeOut timeOut;
}struct_timer;

#define TIME_BASE 50
#define CANT_TIMERS 5


#endif /* HEADERS_TIMEMACHINE_H_ */
