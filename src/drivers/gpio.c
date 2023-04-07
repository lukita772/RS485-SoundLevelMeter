/*
 * gpio.c
 *
 *  Created on: 4 de set. de 2018
 *      Author: lagostini
 */


#include "../headers/headers.h"
/*
uint8_t gpio_set(uint32_t port,uint32_t pin, uint32_t mode)
{
	if((pin > 32) || (port > 4))
		return FAIL;

	if(mode)
		GPIOs[port].FIOSET |= (0x01<<pin);
	else
		GPIOs[port].FIOCLR |= (0x01<<pin);

	return OK;
}

uint8_t gpio_setDir(uint32_t port,uint32_t pin, uint32_t mode)
{
	if((pin > 32) || (port > 4))
		return FAIL;

	if(mode == IN)
		GPIOs[port].FIODIR |= (0x00<<pin);
	else if(mode == OUT)
		GPIOs[port].FIODIR |= (0x01<<pin);

	return OK;
}

uint8_t gpio_get(uint32_t port,uint32_t pin)
{
	uint32_t aux;

	if((pin > 32) || (port > 4))
		return FAIL;

	aux = ((GPIOs[port].FIOPIN) & (0x01 << pin));

	if(!aux)
		return 0;
	else
		return 1;

}
*/

/********************************************************************************
	\Establece un ESTADO en un determinado PIN de un determinado PUERTO
 	\puerto:	puerto con el que se va a trabajar
 	\pin:		pin a activar estado
 	\estado:	valor a establecer en el PIN del PUERTO [0-1].
*/
void gpio_set (uint32_t puerto, uint32_t pin, uint32_t estado)
{
	if (1 == estado)
		GPIOs[puerto].FIOSET = (1 << pin);	//escribir un 1 en FIOSET pone en HIGH el pin
	else
		GPIOs[puerto].FIOCLR = (1 << pin);	//escribir un 1 en FIOCLR pone en LOW el pin
}

/********************************************************************************
	\Establece si un determinado PIN de un determinado PUERTO (previamente configurado como GPIO) es entrada o salida.
 	\puerto: 	puerto con el que se va a trabajar
 	\pin:		pin a configurar sentido
 	\dir:		Direccion 0 = entrada - 1 = salida.
*/
void gpio_setDir (uint32_t puerto, uint32_t pin, uint32_t dir)
{
	if (1 == dir)
		GPIOs[puerto].FIODIR |= (1 << pin);
	else
		GPIOs[puerto].FIODIR &= ~(1 << pin);
}

/********************************************************************************
	\Devuelve el ESTADO de un determinado PIN de un determinado PUERTO.
 	\puerto:	puerto con el que se va a trabajar
 	\pin:		pin a consultar estado
*/
uint32_t gpio_get (uint32_t puerto, uint32_t pin)
{
	return ((GPIOs[puerto].FIOPIN & (1 << pin)) >> pin);
}
