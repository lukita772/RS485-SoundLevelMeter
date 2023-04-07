/*
 * sysTick_Handler.c
 *
 *  Created on: 21 de ago. de 2018
 *      Author: Luca/Matias
 */

#include "../headers/headers.h"
#include <string.h>

#define TIME_LCD_C 5
#define TIME_SLAVE 50
#define TIME_MASTER1 50
#define TIME_MASTER2 500
#define TIME_SAMPLE_FINISHED 5000000
#define TIME_ANTIBOUNCE 1000

extern volatile int Demora_LCD;
volatile uint8_t rs485_flag;
volatile uint8_t rs485_timeout = 0;

void SysTick_initialize (uint32_t x)
{

	if (x > 16777216)
		return;

	STCURR &= ~(0xFFFFFF << 0);
	STRELOAD = x - 1;
	STCTRL |=  ((1 << 0) | (1 << 1) | (1 << 2));
}

void SysTick_Handler(void)
{
	static uint32_t counter_LCD = TIME_LCD_C;
	static uint32_t counter_rs485_slave = TIME_SLAVE;
	static uint32_t counter_rs485_master1 = TIME_MASTER1;
	static uint32_t counter_rs485_master2 = TIME_MASTER2;
	static uint32_t counter_antiBounce = TIME_ANTIBOUNCE;


	counter_LCD--;
	counter_antiBounce--;


	if(counter_LCD == 0)
	{
		Dato_LCD ();
		if(Demora_LCD)
			Demora_LCD--;
		counter_LCD = TIME_LCD_C;
	}


#ifdef MASTER

	if(rs485_flag == TXRX)
		counter_rs485_master1--;

	if(counter_rs485_master1 == 0 && rs485_flag == TXRX )	//Aguardo 10 mseg y paso a modo escucha de TX->RX
	{
		rs485_flag = RX;
		counter_rs485_master1 = TIME_MASTER1;
	}

	if(rs485_flag == RXTX)
		counter_rs485_master2--;

	if(counter_rs485_master2 == 0 && rs485_flag == RXTX)	//Aguardo 500 mseg y transmito, paso RX->TX
	{
		rs485_flag = TX;
		counter_rs485_master2 = TIME_MASTER2;
	}
#else
	if(rs485_flag == TX || rs485_flag == TXRX)
			counter_rs485_slave --;

	if(counter_rs485_slave == 0 && rs485_flag == TX )	//Aguardo 50 mseg y transmito, paso RX->TX
	{
		gpio_set (RTS1, HIGH);							//RTS1 : P0[22] en 1 habilito TX
		RS485_SendStoM(adc_getSampledData());
		rs485_flag = TXRX;
		counter_rs485_slave = TIME_SLAVE;
	}

	if(counter_rs485_slave == 0 && rs485_flag == TXRX)	//Aguardo 50 mseg y paso a modo escucha de TX->RX
	{
		gpio_set (RTS1, LOW);							//RTS1 : P0[22] en 0 habilito RX
		rs485_flag = RX;
		counter_rs485_slave = TIME_SLAVE;
	}

	adc_read();
#endif
/*
	if (counter_antiBounce == 0)//cada 0.1ms
	{
		debounceAnalize();
		counter_antiBounce = TIME_ANTIBOUNCE;
	}
	*/
}


void testLED()
{
	static uint32_t counter = 1000000; //1 segundo (si systick fue configurado en microsegundos)
	static uint8_t flag = 0;

	counter --;

	if(counter == 0)
	{
		flag = !flag;
		gpio_set(TEST_LED, flag);
		counter = 1000000; //<-----cambiar ambos
	}
}


void bzero(void * s, uint8_t n)
{
  char * c = s; // Can't work with void *s directly.
  size_t i;
  for (i = 0; i < n; ++i)
    c[i] = '\0';
}
