#include "../headers/headers.h"

extern volatile unsigned char Buffer_LCD[];


void Display_lcd(char * msg, uint8_t r, uint8_t p)
{
	unsigned int i ;

	switch (r)
	{
		case RENGLON_1:
			Push_LCD(p + 0x80, LCD_CONTROL);
			break;
		case RENGLON_2:
			Push_LCD(p + 0xc0, LCD_CONTROL);
			break;
	}
	for(i = 0 ; msg[i] != '\0' ; i++)
		Push_LCD( msg [i], LCD_DATA);
}
