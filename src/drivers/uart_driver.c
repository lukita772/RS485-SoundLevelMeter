/*
 * uart.c
 *
 *  Created on: 4 de set. de 2018
 *      Author: lagostini
 */

#include "../headers/headers.h"

uint8_t BufferTx[TXBUFFER_SIZE];	//Buffer de Transmision
uint8_t BufferRx[RXBUFFER_SIZE];	//Buffer de Recepcion
uint8_t IndiceTxIn,IndiceTxOut;		//Indices de Transmision
uint8_t IndiceRxIn,IndiceRxOut;		//Indices de Recepcion
uint8_t TxStart;					//flag de TX

/*
// Function to set up UART
void UART0_Init( uint32_t baudrate )
{
	int pclk;
	unsigned long int Fdiv;

	// PCLK_UART0 is being set to 1/4 of SystemCoreClock
	pclk = CORE_CLK / 4;

	// Turn on power to UART0
	PCONP |=  PCUART0_POWERON;

	// Turn on UART0 peripheral clock
	PCLKSEL0 &= ~(PCLK_UART0_MASK);
	PCLKSEL0 |=  (0 << PCLK_UART0);		// PCLK_periph = CCLK/4

	// Set PINSEL0 so that P0.2 = TXD0, P0.3 = RXD0
	PINSEL0 &= ~0xf0;
	PINSEL0 |= ((1 << 4) | (1 << 6));

	//U0LCR = 0x83;		// 8 bits, no Parity, 1 Stop bit, DLAB=1
	U0LCR = 0x0B;
    Fdiv = ( pclk / 16 ) / baudrate ;	// Set baud rate
    U0DLM = Fdiv / 256; //config de velocidad
    U0DLL = Fdiv % 256;

    //-----------------------------------------------------------------------------
    // OJOOOOOO!!! MODIFICACION PARA LOS XBEE SOLAMENTE!!!!!! TIENE 2 BITS DE STOP
    //U0LCR = 0x03;		// 8 bits, no Parity, 2 Stop bit DLAB = 0
    //-----------------------------------------------------------------------------

    //U0FCR = 0x07;		// Enable and reset TX and RX FIFO

	//NVIC_SetPriority(UART0_IRQn, configUART0_INTERRUPT_PRIORITY);
   	//NVIC_EnableIRQ(UART0_IRQn);

    U0IER = IER_RBR | IER_THRE | IER_RLS;	// Enable UART0 interrupt //
}


void UART0_IRQHandler (void)
{
	unsigned char iir,lsr;
	unsigned char IntEnCurso , IntPendiente ;
	int dato ;

	do
	{  //IIR es reset por HW, una vez que lo lei se resetea.

		iir = U0IIR;

		IntPendiente = iir & 0x01;
		IntEnCurso = ( iir >> 1 ) & 0x07;

		switch( IntEnCurso )
		{
			case IIR_RLS:
				lsr = U0LSR;	// con la lectura se borra la int
				if ( lsr & (LSR_OE|LSR_PE|LSR_FE|LSR_RXFE|LSR_BI) )
				{
					dato = U0RBR;		// Leo para borrar el buffer
					return;
				}
			case IIR_RDA:	// Receive Data Available //
				dato = U0RBR;;						// Lectura del dato
				PushRx( (unsigned char ) dato );	// Guardo el dato
				break;

			case IIR_THRE:	//THRE, transmit holding register empty //
			case 0:
				dato = PopTx();						// Tomo el dato a Transmitir
				if ( dato >= 0 )
					U0THR = (unsigned char) dato;	// si hay dato en la cola lo Transmito
				else
					TxStart = 0;
				break;

		}
	}
	while( ! ( IntPendiente & 0x01 ) ); // me fijo si cuando entr‚ a la ISR habia otra
						     	int. pendiente de atenci¢n: b0=1 (ocurre £nicamente si dentro del mismo
								espacio temporal lleguan dos interrupciones a la vez) //
}
*/

void UART1_Init (uint32_t baudrate)
{
	uint32_t pclk, divisor;

	//1.- Registro PCONP: Energizo la UART:
	PCONP |= 0x01<<4;

	//2.- Registro PCLKSEL0 (0x400FC1A8) - selecciono el clk de la UART (recordar que cclk = 100MHz)
	PCLKSEL0 &= ~(0x03<<8);

	//3.- Registro U1LCR (0x4001000C) - transmision de 8 bits, 1 bit de stop, sin paridad, sin break cond, DLAB = 1;
	U1LCR = 0x83;

	//4.- Registros U1DLL (0x40010000) y U1DLM (0x40010004): 9600!
	pclk = CORE_CLK / 4;				// = 25MHz
	divisor = (pclk / 16) / baudrate; 	// = 162,76
    U1DLM = divisor / 256;
    U1DLL = divisor % 256;

	//5.- Registros PINSEL0 (0x4002C000) y PINSEL1 (0x4002C004) - habilitan las funciones especiales de los pines:
    pinConfig_SetPinSel (TX1D, PINSEL_FUNC1);	//TX1D : P0[15] en 1 habilito TX
    pinConfig_SetPinSel (RX1D, PINSEL_FUNC1);	//RX1D : P0[16] en 1 habilito RX

    //RS485
#ifdef MASTER
    gpio_set (RTS1, HIGH);		//RTS1 : P0[22] en 1 habilito TX
#else
    gpio_set (RTS1, LOW);		//RTS1 : P0[22] en 0 habilito RX
#endif

    //6. Habilito las interrupciones (En la UART -IER- y en el NVIC -ISER)
	U1LCR = 0;
	U1LCR = 0x0B; //8 bits data, 1 bit stop, paridad odd (par), DLAB = 0;
	//Habilito interrupción IRX e ITX
    U1IER = 0x03;
    //Habilito interrupción
    ISER0 |= 0x40;
}

void UART1_IRQHandler (void)
{
	uint8_t iir;
	uint32_t dato ;

	//Para limpiar los flags del IIR hay que leerlo, una vez que lo leí se resetea
	do
	{
		iir = U1IIR & 0x07;	//Al IIR le hago una mascara de 111, es decir, me quedo con b2, b1 y b0

		//Hago un corrimiento de 1 bit para la derecha, es decir, leo el b2 y b1
		switch (iir >> 1)
		{
			//RX -> Dato disponible (Interrupción por RX)
			case 2:
				dato = U1RBR;				// Lectura del dato
				PushRx ((uint8_t)dato);		// Guardo el dato
				break;

			//TX -> THR disponible (Interrupción por TX)
			case 1:
				dato = PopTx();						// Tomo el dato a Transmitir
				if (dato != NO_KEY)
					U1THR = (uint8_t)dato;			// Si hay dato en la cola lo Transmito
				else
					TxStart = 0;
				break;

			default:
				break;
		}
	}
	//b0 = 0 => Hay una interrupción pendiente de atención
	//b0 = 1 => No hay una interrupción pendiente
	while ((iir & 0x01) == 0);
}

void PushTx (uint8_t dato)
{
	BufferTx[IndiceTxIn] = dato;

	IndiceTxIn ++;
	IndiceTxIn %= TXBUFFER_SIZE;

	if (TxStart == 0)
	{
		TxStart = 1;				//si no había una TX en curso,
		U1THR = (uint8_t)PopTx();	//fuerzo el inicio de la TX
	}
}

uint32_t PopTx (void)
{
	uint32_t dato = NO_KEY;

	if (IndiceTxIn != IndiceTxOut)
	{
		dato = (uint32_t)BufferTx[IndiceTxOut];
		IndiceTxOut ++;
		IndiceTxOut %= TXBUFFER_SIZE;
	}
	return dato;
}


void PushRx (uint8_t dato)
{
	BufferRx[IndiceRxIn] = dato;
	IndiceRxIn ++;
	if (IndiceRxIn >= RXBUFFER_SIZE)
		IndiceRxIn = 0;
}

uint32_t PopRx (void)
{
	uint32_t dato = NO_KEY;

	if (IndiceRxIn != IndiceRxOut)
	{
		dato = (uint32_t)BufferRx[IndiceRxOut];
		IndiceRxOut ++;
		if (IndiceRxOut >= RXBUFFER_SIZE)
			IndiceRxOut = 0;
	}
	return dato;
}


