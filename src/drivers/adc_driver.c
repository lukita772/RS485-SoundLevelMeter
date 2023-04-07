/*
 * adc_driver.c
 *
 *  Created on: 4 de set. de 2018
 *      Author: Luca
 */

#include "../headers/headers.h"

uint8_t adc_channels[ADC_CHANNEL_QTY] = {0, 1};

uint32_t adc_buffer[ADC_CHANNEL_QTY][SAMPLEQTY]; //ADC_CHANNEL_QTY, SAMPLESQTY

volatile uint32_t sampleIndexIn[ADC_CHANNEL_QTY];
volatile uint32_t sampleIndexOut[ADC_CHANNEL_QTY];


void adc_initialize()
{
	uint16_t i;

	PCONP |= (1 << 12);
	AD0CR = (1 << 21); //pdn enable
	PCLKSEL0 |= (1 << 25); //clk

	//PINSEL1 |= (1 << 14); //set p0.23 as adc0.0
	PINSEL1 |= (1<<16);

	//ISER0 |= ISP_ADC;
	//AD0INTEN |= (1<<0); //habilito interrupcion de adc

	AD0CR |= (1<< 1)|(1<<24);

	for(i = 0; i < ADC_CHANNEL_QTY; i++)
	{
		 sampleIndexIn[i] = 0;
		 sampleIndexOut[i] = 0;
	}

}

void ADC_IRQHandler()
{
	static uint8_t index = 0;

	uint32_t currentSample = AD0GDR;
	currentSample = (currentSample >> 4);  // extraccion de dato del registro
	currentSample &=  0xFFF;               //

	index++;

	if(index > ADC_CHANNEL_QTY)
	{
		index = 0;
	}

	if(currentSample < COUNT_THRESHOLD){
		PushSampledData(currentSample, adc_channels[index]);
	}

	AD0CR &= ~(0xFF);

	ADC_CHANNEL_QTY == 1 ? (AD0CR |= (1<< adc_channels[0])|(1<<24)) : (AD0CR |= (1<< adc_channels[index])|(1<<24));
}


void adc_read()
{
	static uint8_t channel = 1;
	uint32_t currentSample = AD0GDR;

	currentSample = (currentSample >> 4);  // extraccion de dato del registro
	currentSample &=  0xFFF;               //


	switch(channel)
	{
		case 0:
			if(currentSample < COUNT_THRESHOLD) //guardar ultimo resultado resultado del adc0
			{
				PushSampledData(currentSample, adc_channels[channel]);
			}
			AD0CR &= ~(0xFF);
			AD0CR |= (1<<0)|(1<<24); //preparar adc0, y disparar cocnvercion

			break;
		case 1:
			if(currentSample < COUNT_THRESHOLD) //guardar ultimo resultado resultado del adc0
			{
				printf("sample: %d\n",currentSample);
				PushSampledData(currentSample, adc_channels[channel]);
			}
			AD0CR &= ~(0xFF);
			AD0CR |= (1<<1)|(1<<24); //preparar adc1, y disparar cocnvercion

			break;
	}

}


void PushSampledData(uint32_t dato, uint8_t channel)
{
	uint32_t index = sampleIndexIn[channel];
	adc_buffer[channel][index] = dato;
	sampleIndexIn[channel] ++;
	sampleIndexIn[channel] %= SAMPLEQTY;
}

int PopSampledData( uint8_t channel )
{
	int dato = -1;

	if ( sampleIndexIn[channel] != sampleIndexOut[channel] )
	{
		dato =  adc_buffer[channel][sampleIndexOut[channel]];
		sampleIndexOut[channel] ++;
		sampleIndexOut[channel] %= SAMPLEQTY;
	}
	return dato;
}

