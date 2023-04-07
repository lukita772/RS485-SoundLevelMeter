/*
 * main.c
 *
 *  Created on: 25 de nov. de 2018
 *      Author: Matias
 */
#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>

#include <stdio.h>

// TODO: insert other include files here
#include "../headers/headers.h"
// TODO: insert other definitions and declarations here
extern volatile uint8_t rs485_flag;

int main(void) {

	initializeSystem();

    Display_lcd ("OK", 1, 14);

#ifdef MASTER
    rs485_flag = TX;
#endif

    // Enter an infinite loop, just incrementing a counter
    while(1)
    {
#ifdef MASTER
    	RequestToSlave();
#else
    	Analize_MtoS ();
#endif
    }
    return 0 ;
}


