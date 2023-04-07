/*
 * prototypes.h
 *
 *  Created on: 26 de ago. de 2018
 *      Author: Luca
 */

#ifndef HEADERS_PROTOTYPES_H_
#define HEADERS_PROTOTYPES_H_

/*
 * file source: oscilator.c
 */
void initializePLL();

/*
 * file source: initializeSystem.c
 */
void initializeSystem();
void pins_initialize();

/*
 * file source: sysTick_Handler.c
 */
void SysTick_initialize (uint32_t x);
void testLED();
void bzero(void * s, uint8_t n);

/*
 * file source: gpio.c
 */
//uint8_t gpio_get(uint32_t port,uint32_t pin);
//uint8_t gpio_set(uint32_t port,uint32_t pin, uint32_t mode);
//uint8_t gpio_setDir(uint32_t port,uint32_t pin, uint32_t mode);
void gpio_set (uint32_t puerto, uint32_t pin, uint32_t estado);
void gpio_setDir (uint32_t puerto, uint32_t pin, uint32_t dir);
uint32_t gpio_get (uint32_t puerto, uint32_t pin);

/*
 * file source: pinConfig.c
 */
//uint8_t pinConfig_SetPinSel(uint32_t port,uint32_t pin, uint32_t mode);
//uint8_t pinConfig_SetPinMode(uint32_t port,uint32_t pin, uint32_t mode);
void pinConfig_SetPinSel (uint32_t puerto, uint32_t pin, uint32_t funcion);
void pinConfig_SetPinMode (uint32_t puerto, uint32_t pin, uint32_t modo);


/*
 * file source: uart_driver.c
 */
void UART0_Init (uint32_t baudrate);
void UART1_Init (uint32_t baudrate);
void UART1_Init (uint32_t baudrate);
void PushRx (uint8_t dato);
uint32_t PopRx (void);
void PushTx (uint8_t dato);
uint32_t PopTx (void);
void PushSampledData (uint32_t dato, uint8_t channel);
int PopSampledData (uint8_t channel);


/*
 * file source: uart_primitive.c
 */
//void preFilter(uint8_t channel);
uint8_t LeerBufferRX (void);
void Transmitir (uint8_t *v, uint8_t i);


/*
 * file source: timeMachine.c
 */
void timer_initialize();
void timer_set(uint8_t QTimer,T_Time tiempo_prog,void(*func_p)(void));
void timer_countDown();
void timer_analyze();

/*
 * file source: adc_driver.c
 */
void adc_initialize();
void adc_read();

/*
 * file source adc_primitive.c
 */
uint32_t adc_calculateAverageValue(uint8_t channel);
uint8_t adc_countToDbSPL(uint16_t averageValue);
uint8_t adc_getLastMeasuredData();
uint16_t adc_getSampledData();
uint32_t adc_calculateOptimizedAverageValue(uint8_t channel);
void swap(int* a, int* b);
void quicksort(int list[],int m,int n);
int partition (int list[], int low, int high);
int choose_pivot(int i,int j );
double GetDbMin();
double GetDbMax();
double calibrate(uint8_t output, uint8_t input_start, uint8_t input_end, uint8_t output_start, uint8_t output_end);

/*
 * file source: antiBounce_driver.c
 */
int GetKey(uint8_t );
void debounceAnalize (void);
void buttonsInitialize();

/*
 * file source: lcd_driver.c
 */
void Inic_LCD (void);
void Config_LCD (void);
unsigned char Push_LCD (unsigned char, unsigned char);
int Pop_LCD (void);
void Dato_LCD (void);
void Display_LCD (char *, char, char);

/*
 * file source: lcd_primitive.c
 */

void Display_lcd(char * msg, uint8_t r, uint8_t p);

/*
 * file source: checkButtons.c
 */
void CheckButtons();

/*
 * file source: machineState_RS485.c
 */
void RS485_SendStoM (uint8_t);
void Analize_MtoS (void);
uint8_t checkSum (uint8_t *, uint8_t);
void RS485_SendMtoS (uint8_t);
uint8_t Analize_StoM (void);
uint8_t checkSum (uint8_t *, uint8_t);
void deleteDataPacket (uint8_t *, uint8_t);
void RequestToSlave (void);

#endif /* HEADERS_PROTOTYPES_H_ */
