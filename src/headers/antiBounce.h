/*
 * antiBounce.h
 *
 *  Created on: 8 de oct. de 2018
 *      Author: LAGOSTINI
 */

#ifndef HEADERS_ANTIBOUNCE_H_
#define HEADERS_ANTIBOUNCE_H_

#define    TECLAFIJA0    2, 10    //SW1
#define    TECLAFIJA1    0, 18    //SW2

#define	   TECLAFIJA0_KEY	0
#define    TECLAFIJA1_KEY	1

#define CANT_ENT 2


#define BUTTON_HIGH 0
#define BUTTON_LOW	1
#define DEBOUNCE_DELAY 50
#define AFTER_PRESS_BUTTON_DELAY 100


typedef struct
{
    uint8_t lastState;
    uint32_t counter;
    uint8_t active;
} mainButton;



#endif /* HEADERS_ANTIBOUNCE_H_ */
