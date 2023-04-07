/*
 * uart.h
 *
 *  Created on: 4 de set. de 2018
 *      Author: lagostini
 */

#ifndef HEADERS_UART_H_
#define HEADERS_UART_H_

#define	TOPE_BUFFER_TX		100
#define	TOPE_BUFFER_RX		100

/*
// PCUART0
#define PCUART0_POWERON (1 << 3)

#define PCLK_UART0 6
#define PCLK_UART0_MASK (3 << 6)
*/

//#ifdef USE_KIT_INFO2 //test board
	#define	RTS1	0, 22
//#else
//	#define	RTS1	0, 17
//#endif

#define	TX1D	0, 15
#define	RX1D	0, 16
#define RX 		0
#define TX		1
#define TXRX 	2
#define RXTX 	3

//IER
#define IER_RBR		0x01
#define IER_THRE	0x02
#define IER_RLS		0x04

//IIR
#define IIR_PEND	0x01
#define IIR_RLS		0x03
#define IIR_RDA		0x02
#define IIR_CTI		0x06
#define IIR_THRE	0x01

//LSR
#define LSR_RDR		0x01
#define LSR_OE		0x02
#define LSR_PE		0x04
#define LSR_FE		0x08
#define LSR_BI		0x10
#define LSR_THRE	0x20
#define LSR_TEMT	0x40
#define LSR_RXFE	0x80

#define 	TXBUFFER_SIZE	32
#define 	RXBUFFER_SIZE	32
#define		NO_KEY		0xff

//UART0:
//0x4001000CUL : Registro de control de la UART0:
#define		DIR_U0LCR	( ( uint32_t  * ) 0x4000C00CUL )
//0x40010014UL : Registro de recepcion de la UART0:
#define		DIR_U0LSR		( ( uint32_t  * ) 0x4000C014UL )
//0x40010000UL : Parte baja del divisor de la UART0:
#define		DIR_U0DLL	( ( uint32_t  * ) 0x4000C000UL )
//0x40010004UL : Parte alta del divisor de la UART0:
#define		DIR_U0DLM	( ( uint32_t  * ) 0x4000C004UL )
//0x40010000UL : Registro de recepcion de la UART0:
#define		DIR_U0RBR		( ( uint32_t  * ) 0x4000C000UL )
//0x40010000UL : Registro de transmision de la UART0:
#define		DIR_U0THR		( ( uint32_t  * ) 0x4000C000UL )

//UART1:
//0x4001000CUL : Registro de control de la UART1:
#define		DIR_U1LCR	( ( uint32_t  * ) 0x4001000CUL )
//0x40010014UL : Registro de recepcion de la UART1:
#define		DIR_U1LSR		( ( uint32_t  * ) 0x40010014UL )
//0x40010000UL : Parte baja del divisor de la UART1:
#define		DIR_U1DLL	( ( uint32_t  * ) 0x40010000UL )
//0x40010004UL : Parte alta del divisor de la UART1:
#define		DIR_U1DLM	( ( uint32_t  * ) 0x40010004UL )
//0x40010000UL : Registro de recepcion de la UART1:
#define		DIR_U1RBR	( ( uint32_t  * ) 0x40010000UL )
//0x40010000UL : Registro de transmision de la UART1:
#define		DIR_U1THR	( ( uint32_t  * ) 0x40010000UL )
//0x40010004UL : Registro habilitacion de interrupciones de la UART1:
#define		DIR_U1IER	( ( uint32_t  * ) 0x40010004UL )
//0x40010008UL : Registro de identificación de la interrupción de la UART1:
#define		DIR_U1IIR	( ( uint32_t  * ) 0x40010008UL )
//0x40010008UL : Registro de control de la FIFO de la UART1:
#define		DIR_U1FCR	( ( uint32_t  * ) 0x40010008UL )

//Registros de la UART0:
#define		U0THR		DIR_U0THR[0]
#define		U0RBR		DIR_U0RBR[0]
#define		U0LCR		DIR_U0LCR[0]
#define		U0LSR		DIR_U0LSR[0]
#define		U0DLL		DIR_U0DLL[0]
#define		U0DLM		DIR_U0DLM[0]

#define		U0RDR		(U0LSR&0x01)
#define		U0THRE		((U0LSR&0x20)>>5)

//Registros de la UART1:
#define		U1THR		DIR_U1THR[0]
#define		U1RBR		DIR_U1RBR[0]
#define		U1LCR		DIR_U1LCR[0]
#define		U1LSR		DIR_U1LSR[0]
#define		U1DLL		DIR_U1DLL[0]
#define		U1DLM		DIR_U1DLM[0]
#define		U1IER		DIR_U1IER[0]
#define		U1IIR		DIR_U1IIR[0]
#define		U1FCR		DIR_U1FCR[0]

#define		U1RDR		(U1LSR&0x01)
#define		U1THRE		((U1LSR&0x20)>>5)

#define		U1RS485CTRL		DIR_U1RS485CTRL[0]
#define		U1RS485ADRMATCH	DIR_U1RS485ADRMATCH[0]
#define		U1RS485DLY		DIR_U1RS485DLY[0]


#endif /* HEADERS_UART_H_ */
