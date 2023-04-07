/*
 * adc.h
 *
 *  Created on: 5 de set. de 2018
 *      Author: lagostini
 */

#ifndef HEADERS_ADC_H_
#define HEADERS_ADC_H_

#define ADC_CHANNEL_QTY 2
#define SAMPLEQTY 50
#define COUNT_THRESHOLD 4000
#define SENSIBILITY (2.0 / COUNT_THRESHOLD)

//0x40034000UL: Registro de control del ADC:
#define		DIR_AD0CR	( ( uint32_t  * ) 0x40034000UL )
//0x40034004UL: Registro de estado del ADC:
#define		DIR_AD0GDR	( ( uint32_t  * ) 0x40034004UL )
//0x4003400CUL: Registro de interrupcion del ADC
#define		DIR_AD0INTEN ( ( uint32_t  * ) 0x4003400CUL )
//0x40034010UL: Registros de estado de los ADCx
#define		AD0DR		( ( uint32_t  * ) 0x40034010UL )
#define 	ADSTAT 		( ( uint32_t  * ) 0x40034030UL )


//Registros del ADC:
#define		AD0CR		DIR_AD0CR[0]
#define		AD0GDR		DIR_AD0GDR[0]
#define		AD0INTEN	DIR_AD0INTEN[0]

#define		AD0DR0		AD0DR[0]
#define		AD0DR1		AD0DR[1]
#define		AD0DR2		AD0DR[2]
#define		AD0DR3		AD0DR[3]
#define		AD0DR4		AD0DR[4]
#define		AD0DR5		AD0DR[5]
#define		AD0DR6		AD0DR[6]
#define		AD0DR7		AD0DR[7]
#define 	AD0STAT		ADSTAT[0]

#endif /* HEADERS_ADC_H_ */
