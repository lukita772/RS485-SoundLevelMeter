/*
 * adc_primitive.c
 *
 *  Created on: 5 de set. de 2018
 *      Author: Luca
 */


#include "../headers/headers.h"
#include <math.h>

extern uint32_t adc_buffer[ADC_CHANNEL_QTY][SAMPLEQTY];

static double dBMin = 120.0 , dBMax = 50.0;


double GetDbMin()
{
	return dBMin;
}

double GetDbMax()
{
	return dBMax;
}

/*
 * brief: promedio de muestras tomadas por el adc
 * \param uint8_t channel
 */
uint32_t adc_calculateAverageValue(uint8_t channel)
{
	int sampleBuffer = 0;
	int auxBuffer = 0;
	uint32_t i = 0;
	uint8_t sampleCounter = SAMPLEQTY;

	for(i = 0; i < SAMPLEQTY-1 ; i++)
	{
		auxBuffer = PopSampledData(channel);

		if(auxBuffer >= 0){
			sampleBuffer+= auxBuffer;
		}
		else {
			sampleCounter --;
		}

	}

	sampleBuffer /= sampleCounter;

	return sampleBuffer;
}

/*
 * brief: reordenamiento y promedio central de muestras tomadas por el adc
 * \param uint8_t channel
 * TODO: esta fn. aun tiene problemas
 */
uint32_t adc_calculateOptimizedAverageValue(uint8_t channel)
{
	uint16_t sampledArray[SAMPLEQTY], i;
	int initialBuffer = 0;
	uint8_t sampleCounter = 0;
	uint16_t buffer = 0;

	for(i = 0; i < SAMPLEQTY-1 ; i++)
	{
		initialBuffer = PopSampledData(channel);

		if(initialBuffer >= 0)
		{
			sampledArray[sampleCounter] = initialBuffer;
			sampleCounter ++;
		}
	}

	quicksort(sampledArray,0, sampleCounter-1);

	for(i = ((sampleCounter-1)/2)-2; i < ((sampleCounter-1)/2)+2 ; i++)
	{
		buffer+= sampledArray[i];
	}

	buffer /= (((sampleCounter-1)/2)+2 - (((sampleCounter-1)/2)-2));

	return buffer;

}

/*
 * brief: convierte el valor leido en cuentas codificadas por el adc a valores en dbSPL
 * \param: uint16_t averageValue
 */
uint8_t adc_countToDbSPL(uint16_t averageValue)
{
	double buffer;

	if ( averageValue != 0 ) // si da 0, la señal fue muy debil para ser tomada en cuenta
	{
		buffer = (double)averageValue * SENSIBILITY;    //tension de entrada del ADC
		buffer = buffer / 50.0;                   //tension antes del amplificador
		buffer = buffer / 0.0063;                 //presion sonora en micro bar
		buffer = 20.0 * log10 (buffer / 0.00002);       //presion sonora en dB SPL

		buffer = buffer - 25;                          //offset

		if (buffer < dBMin) {
		   dBMin = buffer;
		}

		if (buffer > dBMax) {
		   dBMax = buffer;

		}
	}
	return buffer;
}

/*
 * brief: Expancion de valores. (mapeo)
 * TODO: En test
 */
double calibrate(uint8_t output, uint8_t input_start, uint8_t input_end, uint8_t output_start, uint8_t output_end)
{
	double slope = 1.0 * (output_end - output_start) / (input_end - input_start);
	output = output_start + slope * (output - input_start);

	return output;
}


/*
 * brief: funcion que toma un conjunto de samples hechos por el adc, los promedia, y luego convierte el dato a dbSPL
 */
uint16_t adc_getSampledData()
{
	uint16_t value = 0;

	value = adc_calculateAverageValue(1);
	//value = adc_calculateAverageValue(0);
	value = adc_countToDbSPL(value);

	value = calibrate(value, 60, 80, 30, 100);

	return value;
}


void swap(int *x,int *y)
{
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

int choose_pivot(int i,int j )
{
    return((i+j) /2);
}

void quicksort(int list[],int m,int n)
{
    int key,i,j,k;
    if( m < n)
    {
        k = choose_pivot(m,n);
        swap(&list[m],&list[k]);
        key = list[m];
        i = m+1;
        j = n;
        while(i <= j)
        {
            while((i <= n) && (list[i] <= key))
                i++;
            while((j >= m) && (list[j] > key))
                j--;
            if( i < j)
                swap(&list[i],&list[j]);
        }
        /* swap two elements */
        swap(&list[m],&list[j]);

        /* recursively sort the lesser list */
        quicksort(list,m,j-1);
        quicksort(list,j+1,n);
    }
}
