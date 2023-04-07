/*
 * uart_primitive.c
 *
 *  Created on: 4 de set. de 2018
 *      Author: lagostini
 */

#include "../headers/headers.h"

//TODO: incorporar parametro "uart"
void Transmitir (uint8_t *v, uint8_t i)
{
	uint8_t j;

	for (j = 0; j < i; j++)
		PushTx (v[j]);
}

uint8_t LeerBufferRX (void)
{
	uint8_t caracter;

	caracter = PopRx();
		if (caracter == NO_KEY)
			return NO_KEY;

	return caracter;
}
