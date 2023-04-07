#ifndef HEADERS_LCD_H_
#define HEADERS_LCD_H_


#ifdef USE_KIT_INFO2 //test board
	#define	LCD_RS	2, 6
	#define LCD_E	0, 4
	#define LCD_D4	0, 5
	#define LCD_D5	0, 10
	#define LCD_D6	2, 4
	#define LCD_D7	2, 5
#else
	#define	LCD_RS	0, 2
	#define LCD_E	0, 3
	#define LCD_D4	0, 21
	#define LCD_D5	0, 27
	#define LCD_D6	0, 28
	#define LCD_D7	2, 13
#endif


#define		LCD_CONTROL		1
#define		LCD_DATA		0

#define 	RENGLON_1		0
#define 	RENGLON_2		1
#define 	TOPE_BUFFER_LCD		160



#endif /* HEADERS_LCD_H_ */
