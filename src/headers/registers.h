/*
 * Regs.h
 *
 *  Created on: 04/05/2014
 *      Author: Jorge
 */


#ifndef REGS_H_
#define REGS_H_

typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;
typedef unsigned char uint10_t;

//Estructura para manejar los GPIOs:
typedef struct
{
	uint32_t	FIODIR;
	uint32_t	RESERVED[3];
	uint32_t 	FIOMASK;
	uint32_t 	FIOPIN;
	uint32_t 	FIOSET;
	uint32_t 	FIOCLR;

} gpio_t;


//Estructura para manejar los Timers:
typedef struct
{
	uint32_t	IR;
	uint32_t	TCR;
	uint32_t 	TC;
	uint32_t 	PR;
	uint32_t 	PC;
	uint32_t 	MCR;
	uint32_t	MR0;
	uint32_t	MR1;
	uint32_t	MR2;
	uint32_t	MR3;
	uint32_t	CCR;
	uint32_t	CR0;
	uint32_t	CR1;

} timer_t;


//Registros generales:
//0x4002C000UL : Direccion de inicio de los registros PINSEL
#define		PINSEL		( ( uint32_t  * ) 0x4002C000UL )
//0x2009C000UL : Direccion de inicio de los registros de GPIOs
#define		GPIOs		( ( gpio_t  * ) 0x2009C000UL )
//0x400FC0C4UL : Direccion de inicio del registro de habilitación de dispositivos:
#define 	DIR_PCONP	( ( uint32_t  * ) 0x400FC0C4UL )
//0x400FC1A8UL : Direccion de inicio de los registros de seleccion de los clks de los dispositivos:
#define		PCLKSEL		( ( uint32_t  * ) 0x400FC1A8UL )
//0x4002C040UL : Direccion de inicio de los registros de modo de los pines del GPIO
#define		PINMODE		( ( uint32_t  * ) 0x4002C040UL )
//0xE000E100UL : Dir. inicio reg. habilitación (set) de interrup. en el NVIC:
#define		ISER		( ( uint32_t  * ) 0xE000E100UL )
//0xE000E180UL : Direccion de inicio de los registros de deshabilitacion (clear) de interrupciones en el NVIC:
#define		ICER		( ( uint32_t  * ) 0xE000E180UL )


//Registros Interrupciones EXTERNAS
#define		EXTINT		( ( uint32_t *  ) 0x400FC140UL )//contiene flags EINT0 EINT1 EINT2 EINT3  T.10
#define		EXTMODE		( ( uint32_t *  ) 0x400FC148UL )//reg. seteo si interr.  flanco o nivel T.11
#define		EXTPOLAR	( ( uint32_t *  ) 0x400FC14CUL )//reg. seteo si flanc./niv. es posit. o negat.  T.12
#define		IOintStatus	( ( uint32_t *  ) 0x40028080UL )//indica interrup pendiente si hay "1" en bit 0 P0,
                                                            //indica interrup pendiente si hay "1" en bit 2 P2 T113
// P2[10] EINT0 NMI, P2[11] EINT1 I2STX_CLK, P2[12] EINT2 I2STX_WS, P2[13] EINT3 I2STX_SDA
#define		EXTMODE0	EXTMODE[0]	// 		(0x400FC148)
//	EXTMODE1   es EXTMODE[0] desplazado un bit si a la izquier. EXTMODE|=(1<<1);
//	EXTMODE2   es EXTMODE[0] desplazado Dosb bit   (2<<1)     EXTMODE|=(2<<1);
//	EXTMODE3   es EXTMODE[0] desplazado Tres bit   (3<<1)	 EXTMODE|=(3<<1);//selecto por Flanco con Uno

//	EINT0   es   EXTINT[0]   EXINT|=1;   //reseteo flag de EINT0          reseteo flag de EINT0
//	EINT1   es   EXTINT[0] desplazado un bit a la izquier. EXINT|=(1<<1);//reseteo flag de EINT1
//	EINT2   es   EXTINT[0] desplazado Dosb bit   (2<<1)    EXINT|=(2<<1);//reseteo flag de EINT2
//	EINT3   es   EXTINT[0] desplazado Tres bit   (3<<1)	   EXINT|=(3<<1);//reseteo Flag de EINT3


#define		IO0intStatR		( ( uint32_t *  ) 0x40028084UL )//Status int.port0 por flanco Ascendente T.118
#define		IO0intStatF		( ( uint32_t *  ) 0x40028088UL )//Status int.port0 por flanco Descendente T.120
#define     IO0intClr      	( ( uint32_t * )  0x4002808CUL )//Escribo un uno limpia la interrupción  T.122
#define     IO0intEnR       ( ( uint32_t *  ) 0x40028090UL )//enable int.port0 por flanco ascendente T.114
#define		IO0intEnF		( ( uint32_t *  ) 0x40028094UL )//enable int.port0 por flanco descendente T.116
//#define   RESERVED        ( ( uint32_t  * ) 0x40028098UL )//ERROR Tabla 102
//#define   RESERVED        ( ( uint32_t  * ) 0x4002809CUL )
//#define   RESERVED        ( ( uint32_t  * ) 0x400280A0UL )
#define		IO2intStatR		( ( uint32_t *  ) 0x400280A4UL )//Status int.port2 por flanco Ascendente T.119
#define		IO2intStatF		( ( uint32_t * ) 0x400280A8UL )//Status int.port2 por flanco Descendente T.121
#define     IO2intClr      	( ( uint32_t * )  0x400280ACUL )//Escribo un uno limpia la interrupción  T.123
#define		IO2intEnR		( ( uint32_t *  ) 0x400280B0UL )//enable int.port2 por flanco ascendente T.115
#define		IO2intEnF		( ( uint32_t *  ) 0x400280B4UL )//enable int.port2 por flanco descendente T.117


//Timers:
//0x40004000UL : Direccion de inicio de los registros del Timer0
#define		DIR_TIMER0		( ( timer_t  * ) 0x40004000UL )
//0x40008000UL : Direccion de inicio de los registros del Timer1
#define		DIR_TIMER1		( ( timer_t  * ) 0x40008000UL )
//0x40090000UL : Direccion de inicio de los registros del Timer2
#define		DIR_TIMER2		( ( timer_t  * ) 0x40090000UL )
//0x40094000UL : Direccion de inicio de los registros del Timer3
#define		DIR_TIMER3		( ( timer_t  * ) 0x40094000UL )

//0x4008C000UL : Registro de conversion del DAC:
#define		DIR_DACR	( ( uint32_t  * ) 0x4008C000UL )
//0x4008C004UL : Registro de control del DAC:
#define		DIR_DACCTRL	( ( uint32_t  * ) 0x4008C004UL )
//0x4008C008UL : Registro de contador del DAC:
#define		DIR_DACCNTVAL ( ( uint32_t  * ) 0x4008C008UL )



//Registros del CLOCK y de sistema:
//0x400FC1A0UL: Registro de control de sistema y registro de status:
#define	DIR_SCS	( (uint32_t *) 0x400FC1A0UL)
//0x400FC104UL: Registro de configuracion del clock:
#define	DIR_CCLKCFG	( (uint32_t *) 0x400FC104UL)
//0x400FC10CUL: Registro de seleccion del clock:
#define	DIR_CLKSRCSEL	( (uint32_t *) 0x400FC10CUL)
//0x400FC1C8UL: Clock Output Config register:
#define	DIR_CLKOUTCFG	( (uint32_t *) 0x400FC1C8UL)
//0x400FC000UL: Flash access configuration:
#define	DIR_FLASHCFG	( (uint32_t *) 0x400FC000UL)

//Registros de los PLL:
//0x400FC080UL: Registro de control del PLL0:
#define	DIR_PLL0CON	( (uint32_t *) 0x400FC080UL)
//0x400FC084UL: Registro de configuracion del PLL0:
#define	DIR_PLL0CFG	( (uint32_t *) 0x400FC084UL)
//0x400FC088UL: Registro de estado del PLL0:
#define	DIR_PLL0STAT	( (uint32_t *) 0x400FC088UL)
//0x400FC08CUL: Registro de control del PLL0:
#define	DIR_PLL0FEED	( (uint32_t *) 0x400FC08CUL)
//0x400FC0A0UL: Registro de control del PLL1:
#define	DIR_PLL1CON	( (uint32_t *) 0x400FC0A0UL)
//0x400FC0A4UL: Registro de configuracion del PLL1:
#define	DIR_PLL1CFG	( (uint32_t *) 0x400FC0A4UL)
//0x400FC0A8UL: Registro de estado del PLL1:
#define	DIR_PLL1STAT	( (uint32_t *) 0x400FC0A8UL)
//0x400FC0ACUL: Registro de control del PLL1:
#define	DIR_PLL1FEED	( (uint32_t *) 0x400FC0ACUL)


//Registros del SysTick:
#define MAX_TICKS		0x00fffffful
//0xE000E010UL: Registro de control del SysTick:
#define DIR_STCTRL		( (uint32_t *) 0xE000E010UL)
//0xE000E014UL: Registro de recarga del SysTick:
#define DIR_STRELOAD	( (uint32_t *) 0xE000E014UL)
//0xE000E018UL: Registro de cuenta del SysTick:
#define DIR_STCURR		( (uint32_t *) 0xE000E018UL)
//0xE000E01CUL: Registro de calibracion del SysTick:
#define DIR_STCALIB		( (uint32_t *) 0xE000E01CUL)

#define ENABLE 			(0x01 << 0)
#define TICKINT			(0x01 << 1)
#define CLKSOURCE 		(0x01 << 2)


//Registros PINSEL:

#define		PINSEL0		PINSEL[0]	//!< PINSEL0------>P0[15:0] 		(0x4002C000)
#define		PINSEL1		PINSEL[1]	//!< PINSEL1------>P0[31:16] 		(0x4002C004)
#define		PINSEL2		PINSEL[2]	//!< PINSEL2------>P1[15:0] 		(0x4002C008)
#define		PINSEL3		PINSEL[3]	//!< PINSEL3------>P1[31:16] 		(0x4002C00C)
#define		PINSEL4		PINSEL[4]	//!< PINSEL4------>P2[15:0] 		(0x4002C010)
#define		PINSEL5		PINSEL[5]	//!< PINSEL5------>P2[31:16] 		NOT USED
#define		PINSEL6		PINSEL[6]	//!< PINSEL6------>P3[15:0]		  NOT USED
#define		PINSEL7		PINSEL[7]	//!< PINSEL7------>P3[31:16] 		(0x4002C01C)
#define		PINSEL8		PINSEL[8]	//!< PINSEL8------>P4[15:0]		  NOT USED
#define		PINSEL9		PINSEL[9]	//!< PINSEL9------>P4[31:16] 		(0x4002C024)


//Registros PINMODE
#define		PINMODE0	PINMODE[0]
#define		PINMODE1	PINMODE[1]
#define		PINMODE2	PINMODE[2]
#define		PINMODE3	PINMODE[3]
#define		PINMODE4	PINMODE[4]
#define		PINMODE5	PINMODE[5]
#define		PINMODE6	PINMODE[6]
#define		PINMODE7	PINMODE[7]
#define		PINMODE8	PINMODE[8]
#define		PINMODE9	PINMODE[9]

//Registros GPIOs:
#define		GPIO0		GPIOs[0]
#define		GPIO1		GPIOs[1]
#define		GPIO2		GPIOs[2]
#define		GPIO3		GPIOs[3]
#define		GPIO4		GPIOs[4]

#define		FIO0DIR		GPIO0.FIODIR
#define		FIO1DIR		GPIO1.FIODIR
#define		FIO2DIR		GPIO2.FIODIR
#define		FIO3DIR		GPIO3.FIODIR
#define		FIO4DIR		GPIO4.FIODIR

#define		FIO0MASK	GPIO0.FIOMASK
#define		FIO1MASK	GPIO1.FIOMASK
#define		FIO2MASK	GPIO2.FIOMASK
#define		FIO3MASK	GPIO3.FIOMASK
#define		FIO4MASK	GPIO4.FIOMASK

#define		FIO0CLR		GPIO0.FIOCLR
#define		FIO1CLR		GPIO1.FIOCLR
#define		FIO2CLR		GPIO2.FIOCLR
#define		FIO3CLR		GPIO3.FIOCLR
#define		FIO4CLR		GPIO4.FIOCLR

#define		FIO0SET		GPIO0.FIOSET
#define		FIO1SET		GPIO1.FIOSET
#define		FIO2SET		GPIO2.FIOSET
#define		FIO3SET		GPIO3.FIOSET
#define		FIO4SET		GPIO4.FIOSET

#define		FIO0PIN		GPIO0.FIOPIN
#define		FIO1PIN		GPIO1.FIOPIN
#define		FIO2PIN		GPIO2.FIOPIN
#define		FIO3PIN		GPIO3.FIOPIN
#define		FIO4PIN		GPIO4.FIOPIN

//Registros de timers:
#define		TIMER0		DIR_TIMER0[0]
#define		TIMER1		DIR_TIMER1[0]
#define		TIMER2		DIR_TIMER2[0]
#define		TIMER3		DIR_TIMER3[0]

#define		T0IR		TIMER0.IR
#define		T1IR		TIMER1.IR
#define		T2IR		TIMER2.IR
#define		T3IR		TIMER3.IR

#define		T0TCR		TIMER0.TCR
#define		T1TCR		TIMER1.TCR
#define		T2TCR		TIMER2.TCR
#define		T3TCR		TIMER3.TCR

#define		T0PC		TIMER0.PC
#define		T1PC		TIMER1.PC
#define		T2PC		TIMER2.PC
#define		T3PC		TIMER3.PC

#define		T0MCR		TIMER0.MCR
#define		T1MCR		TIMER1.MCR
#define		T2MCR		TIMER2.MCR
#define		T3MCR		TIMER3.MCR

#define		T0MR0		TIMER0.MR0
#define		T1MR0		TIMER1.MR0
#define		T2MR0		TIMER2.MR0
#define		T3MR0		TIMER3.MR0

#define		T0MR1		TIMER0.MR1
#define		T1MR1		TIMER1.MR1
#define		T2MR1		TIMER2.MR1
#define		T3MR1		TIMER3.MR1

#define		T0MR2		TIMER0.MR2
#define		T1MR2		TIMER1.MR2
#define		T2MR2		TIMER2.MR2
#define		T3MR2		TIMER3.MR2

#define		T0MR3		TIMER0.MR3
#define		T1MR3		TIMER1.MR3
#define		T2MR3		TIMER2.MR3
#define		T3MR3		TIMER3.MR3

#define		T0CCR		TIMER0.CCR
#define		T1CCR		TIMER1.CCR
#define		T2CCR		TIMER2.CCR
#define		T3CCR		TIMER3.CCR

#define		T0CR0		TIMER0.CR0
#define		T1CR0		TIMER1.CR0
#define		T2CR0		TIMER2.CR0
#define		T3CR0		TIMER3.CR0

#define		T0CR1		TIMER0.CR1
#define		T1CR1		TIMER1.CR1
#define		T2CR1		TIMER2.CR1
#define		T3CR1		TIMER3.CR1

//Registros ISER:
#define		ISER0		ISER[0]
#define		ISER1		ISER[1]

//Registros ICER:
#define		ICER0		ICER[0]
#define		ICER1		ICER[1]

//Registro PCONP:
#define		PCONP		DIR_PCONP[0]

//Registros PCLKSEL
#define		PCLKSEL0	PCLKSEL[0]
#define		PCLKSEL1	PCLKSEL[1]

//Registros del DAC:
#define		DACR		DIR_DACR[0]
#define		DACCTRL		DIR_DACCTRL[0]
#define		DACCNTVAL	DIR_DACCNTVAL[0]


//Registro de status y configuracion del sistema:
#define	SCS			DIR_SCS[0]
#define FLASHCFG	DIR_FLASHCFG[0]

//Registros de control del CLOCK:
#define	CCLKCFG		DIR_CCLKCFG[0]
#define	CLKSRCSEL	DIR_CLKSRCSEL[0]
#define	CLKOUTCFG	DIR_CLKOUTCFG[0]

//PLL0:
#define	PLL0CON		DIR_PLL0CON[0]
#define	PLL0CFG		DIR_PLL0CFG[0]
#define	PLL0STAT	DIR_PLL0STAT[0]
#define	PLL0FEED	DIR_PLL0FEED[0]

//PLL1:
#define	PLL1CON		DIR_PLL1CON[0]
#define	PLL1CFG		DIR_PLL1CFG[0]
#define	PLL1STAT	DIR_PLL1STAT[0]
#define	PLL1FEED	DIR_PLL1FEED[0]

//Systick:
#define STCTRL		DIR_STCTRL[0]
#define STCALIB		DIR_STCALIB[0]
#define STCURR		DIR_STCURR[0]
#define STRELOAD	DIR_STRELOAD[0]


// nuevos mapeos.--------------------------------------------------------------------------
//#define PINMODE_OD_INDEX (volatile uint32_t *) 0x2009C068UL
#define XTAL        		(12000000UL)        /* Oscillator frequency               */
#define OSC_CLK     		(      XTAL)        /* Main oscillator frequency          */
#define RTC_CLK     		(   32000UL)        /* RTC oscillator frequency           */
#define IRC_OSC     		( 4000000UL)        /* Internal RC oscillator frequency   */

/* F_cco0 = (2 * M * F_in) / N  */
#define CCLKCFG_Val       	0x00000003
#define _M               	(((PLL0CFG_Value      ) & 0x7FFF) + 1)
#define _N               	(((PLL0CFG_Value >> 16) & 0x00FF) + 1)
#define _FCCO(_F_IN)    	((2ULL * _M * _F_IN) / _N)
#define _CCLK_DIV        	(((CCLKCFG_Val      ) & 0x00FF) + 1)

/* Determine core clock frequency according to settings */
#define CORE_CLK			(_FCCO(OSC_CLK) / _CCLK_DIV)



// Interrupt Set-Pending Registers
#define		DIR_ISPR 		( ( uint32_t  * ) 0xE000E200UL )
#define		ISPR			DIR_ISPR[0]
#define		ISP_UART0		(1 << 5)
#define		ISP_UART1		(1 << 6)
#define		ISP_EINT3		(1 << 21)
#define		ISP_ADC			(1 << 22)
#define		ISP_DMA			(1 << 26)

#endif /* REGS_H_ */


