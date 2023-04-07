/*
 * antiBounce_driver.c
 *
 *  Created on: 8 de oct. de 2018
 *      Author: LAGOSTINI
 */

#include "../headers/headers.h"

volatile mainButton mainButtons[CANT_ENT];

void buttonsInitialize()
{
	uint16_t i;

	for(i = 0; i < CANT_ENT; i++)
	{
		mainButtons[i].active = LOW;
		mainButtons[i].lastState  = HIGH;
	}
}

void debounceAnalize (void)
{
    uint8_t i;
    uint32_t currentState = 0;
    static uint32_t afterPressDelay = 0;

    if(afterPressDelay != 0){
    	afterPressDelay --;
    }

    for(i = 0; i < CANT_ENT; i++)
    {
        switch(i)    //La cantidad de case depende de la cantidad de entradas!!!
        {
            case 0:
                currentState = gpio_get(TECLAFIJA0);
                break;

            case 1:
            	currentState = gpio_get(TECLAFIJA1);
                break;

            default:
                break;
        }

        if(currentState != mainButtons[i].lastState){
        	mainButtons[i].counter = 0;
        }

        if((currentState == mainButtons[i].lastState) && currentState == BUTTON_HIGH && afterPressDelay == 0)
        {
        	mainButtons[i].counter++;

        	if(mainButtons[i].counter > DEBOUNCE_DELAY)
        	{
        		mainButtons[i].active = HIGH;
        		mainButtons[i].counter = 0;
        		afterPressDelay = AFTER_PRESS_BUTTON_DELAY; //espero 1ms hasta poder tocar de nuevo
        	}
        }

        mainButtons[i].lastState = currentState;
    }
}

//TODO: validar key
int GetKey(uint8_t key)
{
	uint8_t keyData;

	if(key < CANT_ENT)
	{
		keyData = mainButtons[key].active;
		mainButtons[key].active = LOW;
	}
	else
	{
		keyData = NO_KEY;
	}

	return keyData;
}
