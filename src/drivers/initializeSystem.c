/*
 *
 *  Created on: 26 de ago. de 2018
 *      Author: Luca/Matias
 */

#include "../headers/headers.h"

void initializeSystem()
{
	initializePLL();

	pins_initialize();
	adc_initialize();
	//timer_initialize();
	SysTick_initialize(MILISECOND);
	Inic_LCD();
	UART1_Init (9600);
	buttonsInitialize();


}

void pins_initialize()
{
	//pinConfig_SetPinSel(0,23, PINSEL_FUNC1); //p0.23 : modo 01 : adc (adc0.0)
	//pinConfig_SetPinMode(0,23, PINMODE_NONE);

	pinConfig_SetPinSel (0, 17, PINSEL_GPIO);
	pinConfig_SetPinMode (0,17, PINMODE_NONE);
	gpio_setDir(0, 17, OUT);
//	gpio_set(0,17, 1);
	/*
	pinConfig_SetPinSel(TECLAFIJA0, PINSEL_GPIO);         // puerto = 2 , pin = 10 ; funcion = 0 = GPIO
	pinConfig_SetPinMode(TECLAFIJA0, PINMODE_PULLUP);     // puerto = 2 , pin = 10 ; modo = 0 = PULLUP
	gpio_setDir(TECLAFIJA0, IN);                         // puerto = 2 , pin = 10 ; dir = 0 = ENTRADA

	pinConfig_SetPinSel(TECLAFIJA1, PINSEL_GPIO);         // puerto = 0 , pin = 18 ; funcion = 0 = GPIO
	pinConfig_SetPinMode(TECLAFIJA1, PINMODE_PULLUP);     // puerto = 0 , pin = 18 ; modo = 0 = PULLUP
	gpio_setDir(TECLAFIJA1, IN);                         // puerto = 0 , pin = 18 ; dir = 0 = ENTRADA
	*/
}

