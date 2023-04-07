/*
 * checkButtons.c
 *
 *  Created on: 8 de oct. de 2018
 *      Author: LAGOSTINI
 */


#include "../headers/headers.h"

void CheckButtons()
{
	char dataBuffer[30];

    if (GetKey(TECLAFIJA0_KEY))
    {
        gpio_set(0, 22, 1);    //PRENDO LED
		//RS485
		//RTS1 : P0[22]
		//PINSEL1 |= 0x01<<12;
		//RS485_SendStoM (23);
		//Transmitir(dataBuffer); //uart
    }

    //if (GetKey(TECLAFIJA1_KEY))
    //    gpio_set(TEST_LED, TECLAFIJA1_KEY);    //APAGO LED
}
