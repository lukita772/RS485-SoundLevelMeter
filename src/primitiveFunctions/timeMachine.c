/*
 * timeMachine.c
 *
 *  Created on: 26 de ago. de 2018
 *      Author: Luca
 */

#include "../headers/headers.h"

volatile struct_timer TIMER[CANT_TIMERS];

#define NULL (void*)0;

void timer_initialize()
{
	int i;

	for(i = 0; i < CANT_TIMERS;i++)
	{
		TIMER[i].timeOut = 0;
		TIMER[i].time = 0;
		TIMER[i].func_p = NULL;
	}
}

void timer_set(uint8_t QTimer,T_Time tiempo_prog,void(*func_p)(void))
{
	if(QTimer < CANT_TIMERS)
	{
		TIMER[QTimer].time = tiempo_prog;
		TIMER[QTimer].timeOut = 0;
		TIMER[QTimer].func_p = func_p;
	}
}

void timer_countDown()
{
	static int CONT = 0;
	int i;

	if(CONT >= TIME_BASE)
	{
		for(i = 0; i < CANT_TIMERS;i++)
		{
			if(TIMER[i].time >0)
				TIMER[i].time --;

			else if(TIMER[i].time == 0)
				TIMER[i].timeOut =1;
		}
		CONT = 0;
	}
	CONT ++;


}

void timer_analyze()
{
	int i;

	for(i = 0; i < CANT_TIMERS;i++)
	{
		if(TIMER[i].timeOut == 1)
		{
			if(TIMER[i].func_p) // si el puntero esta apuntando a algo
				(TIMER[i].func_p)(); //ejecuto la funcion

			TIMER[i].timeOut = 0;
		}
	}
}
