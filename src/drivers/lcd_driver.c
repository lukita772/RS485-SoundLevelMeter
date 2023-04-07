/**
 	\file KitInfo2FW_LCD.c
 	\brief Drivers del LCD
 	\details Validas para LCD de 4 bits de direccionamiento
 	\author Ing. Marcelo Trujillo
 	\date 2012.04.25
*/
#include "../headers/headers.h"

// TODO: insert other definitions and declarations here
volatile uint32_t Demora_LCD;
uint8_t Buffer_LCD [TOPE_BUFFER_LCD];
uint32_t inxInLCD;
uint32_t inxOutLCD;
uint32_t cantidadColaLCD;

void Inic_LCD(void)
{

	pinConfig_SetPinSel(LCD_RS, PINSEL_GPIO);
	gpio_setDir(LCD_RS, OUT);	// RS
	pinConfig_SetPinSel(LCD_E, PINSEL_GPIO);
	gpio_setDir(LCD_E, OUT);	// E
	pinConfig_SetPinSel(LCD_D4, PINSEL_GPIO);
	gpio_setDir(LCD_D4, OUT);	// D4
	pinConfig_SetPinSel(LCD_D5, PINSEL_GPIO);
	gpio_setDir(LCD_D5, OUT);	// D5
	pinConfig_SetPinSel(LCD_D6, PINSEL_GPIO);
	gpio_setDir(LCD_D6, OUT);	// D6
	pinConfig_SetPinSel(LCD_D7, PINSEL_GPIO);
	gpio_setDir(LCD_D7, OUT);	// D7

	Config_LCD( );
}

void Config_LCD(void)
{
	unsigned int i;

	gpio_set(LCD_E, OFF);
	Demora_LCD = 4;					// Demora inicial
	while (Demora_LCD);

	for( i = 0 ; i < 3 ; i++ )
	{
		gpio_set(LCD_D4, HIGH);		// Configuracion en 8 bits
		gpio_set(LCD_D5, HIGH);
		gpio_set(LCD_D6, LOW);
		gpio_set(LCD_D7, LOW);

		gpio_set(LCD_RS, LOW);
		gpio_set(LCD_E, HIGH);
		gpio_set(LCD_E, LOW);
		Demora_LCD = 1;
		while (Demora_LCD);
	}

	// Configuracion en 4 bits
	gpio_set(LCD_D4, LOW);
	gpio_set(LCD_D5, HIGH);
	gpio_set(LCD_D6, LOW);
	gpio_set(LCD_D7, LOW);

	gpio_set(LCD_RS, LOW);
	gpio_set(LCD_E, HIGH);
	gpio_set(LCD_E, LOW);

	Demora_LCD = 1;	// Demora inicial
	while (Demora_LCD);

	// A partir de aca el LCD pasa a 4 bits !!!
	Push_LCD(0x28, LCD_CONTROL );	// DL = 0: 4 bits de datos
									// N = 1 : 2 lineas
									// F = 0 : 5x7 puntos

	Push_LCD(0x08, LCD_CONTROL);	// D = 0 : display OFF
									// C = 0 : Cursor OFF
									// B = 0 : Blink OFF

	Push_LCD(0x01, LCD_CONTROL);	// clear display

	Push_LCD(0x06, LCD_CONTROL);	// I/D = 1 : Incrementa puntero
									// S = 0 : NO Shift Display

	// Activo el LCD y listo para usar !
	Push_LCD(0x0C, LCD_CONTROL);	// D = 1 : display ON
									// C = 0 : Cursor OFF
									// B = 0 : Blink OFF
}

unsigned char Push_LCD(unsigned char dato, unsigned char control )
{
	if (cantidadColaLCD >= TOPE_BUFFER_LCD )
		return -1;

	Buffer_LCD [ inxInLCD ] = ( dato >> 4 ) & 0x0f;
	if ( control == LCD_CONTROL )
		Buffer_LCD [ inxInLCD ] |= 0x80;

	inxInLCD ++;
	inxInLCD %= TOPE_BUFFER_LCD;

	Buffer_LCD [ inxInLCD ] = dato & 0x0f;
	if ( control == LCD_CONTROL )
		Buffer_LCD [ inxInLCD ] |= 0x80;

	cantidadColaLCD += 2;

	inxInLCD ++;
	inxInLCD %= TOPE_BUFFER_LCD;

	return 0;
}

int PopLCD ( void )
{
	char dato;

	if ( cantidadColaLCD == 0 )
		return -1;

	dato = Buffer_LCD [ inxOutLCD ] ;

	cantidadColaLCD --;

	inxOutLCD ++;
	inxOutLCD %= TOPE_BUFFER_LCD;

	return dato;
}

void Dato_LCD(void)
{
	int data;
	int j;
	if ( (data = PopLCD ()) == -1 )
		return;

	gpio_set(LCD_D7,((unsigned char ) data ) >> 3 & 0x01);
	gpio_set(LCD_D6,((unsigned char ) data ) >> 2 & 0x01);
	gpio_set(LCD_D5,((unsigned char ) data ) >> 1 & 0x01);
	gpio_set(LCD_D4,((unsigned char ) data ) >> 0 & 0x01);

	if( ((unsigned char ) data ) & 0x80 )
		gpio_set(LCD_RS, LOW);	//Comando
	else
		gpio_set(LCD_RS, HIGH);	//Dato

	gpio_set(LCD_E, HIGH);
	for(j=0; j<1000; j++);
	gpio_set(LCD_E, LOW);
	for(j=0; j<1000; j++);
}
