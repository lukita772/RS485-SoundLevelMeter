/*
 * pinConfig.c
 *
 *  Created on: 4 de set. de 2018
 *      Author: lagostini
 */

#include "../headers/headers.h"
/*
uint8_t pinConfig_SetPinSel(uint32_t port,uint32_t pin, uint32_t mode)
{
		if(pin > 15)
		{
			if(pin > 31)
				return FAIL;

			if(mode == PINSEL_GPIO)
				PINSEL[(port*2)+1] = (0x00<<(pin-16));
			else if(mode == PINSEL_FUNC1)
				PINSEL[(port*2)+1] = (0x01<<(pin-16));
			else if(mode == PINSEL_FUNC2)
				PINSEL[(port*2)+1] = (0x02<<(pin-16));
			else if(mode == PINSEL_FUNC3)
				PINSEL[(port*2)+1] = (0x03<<(pin-16));

			return OK;
		}
		else
		{
			if(mode == PINSEL_GPIO)
					PINSEL[port*2] = (0x00<<(pin));
			else if(mode == PINSEL_FUNC1)
					PINSEL[port*2] = (0x01<<(pin));
			else if(mode == PINSEL_FUNC2)
					PINSEL[port*2] = (0x02<<(pin));
			else if(mode == PINSEL_FUNC3)
					PINSEL[port*2] = (0x03<<(pin));

			return OK;
		}

}

uint8_t pinConfig_SetPinMode(uint32_t port,uint32_t pin, uint32_t mode)
{
		if(pin > 15)
		{
			if(pin > 31)
				return FAIL;

			if(mode == PINMODE_PULLUP)
				PINMODE[(port*2)+1] = (0x00<<(pin-16));
			else if(mode == PINMODE_REPEAT)
				PINMODE[(port*2)+1] = (0x01<<(pin-16));
			else if(mode == PINMODE_NONE)
				PINMODE[(port*2)+1] = (0x02<<(pin-16));
			else if(mode == PINMODE_PULLDOWN)
				PINMODE[(port*2)+1] = (0x03<<(pin-16));

			return OK;
		}
		else
		{
			if(mode == PINMODE_PULLUP)
				PINMODE[port*2] = (0x00<<(pin));
			else if(mode == PINMODE_REPEAT)
				PINMODE[port*2] = (0x01<<(pin));
			else if(mode == PINMODE_NONE)
				PINMODE[port*2] = (0x02<<(pin));
			else if(mode == PINMODE_PULLDOWN)
				PINMODE[port*2] = (0x03<<(pin));

			return OK;
		}
}

*/

/********************************************************************************
	\Selección de modo de los puertos (4 modos).
 	\puerto:	puerto a configurar
 	\pin:		pin del port a configurar
 	\funcion:	selección de la funcion que tendra el pin  [0 - 3] / 0 = GPIO
*/
void pinConfig_SetPinSel (uint32_t puerto, uint32_t pin, uint32_t funcion)
{
	puerto = puerto*2 + pin/16;
	pin = (pin%16)*2;

	PINSEL[puerto] &= ~(3 << pin);
	if (funcion != 0)
		PINSEL[puerto] |= (funcion << pin);
}

/********************************************************************************
	\Selección de modo de trabajo del puerto cuando es configurado como entrada
 	\puerto:	puerto a configurar
 	\pin:		pin del port a configurar
 	\modo:		selección de la funcion que tendra el pin  [0 - 3] / 0 = pullup - 1 = pulldown
*/
void pinConfig_SetPinMode (uint32_t puerto, uint32_t pin, uint32_t modo)
{
	puerto = puerto*2 + pin/16;
	pin = (pin%16)*2;

	PINMODE[puerto] &= ~(3 << pin);
	if (modo != 0)
		PINMODE[puerto] |= (modo << pin);
}

