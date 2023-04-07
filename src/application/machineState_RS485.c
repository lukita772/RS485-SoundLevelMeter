/*
 * machinstateate_RS485.c
 *
 *  Created on: 25 de nov. de 2018
 *      Author: Matias
 */

#include "../headers/headers.h"

#define IDSLAVE 3
extern volatile uint8_t rs485_flag;
extern volatile uint8_t rs485_timeout;


// ********************************************** SLAVE ********************************************** //
// +++ FUNCIONES PARA ARMAR TRAMA Y ENVIAR +++
void RS485_SendStoM (uint8_t data)
{
//	static uint8_t data = 10;
	uint8_t vec[7];
	uint8_t aux[2];
	uint8_t chk;
	char str[7];

	vec[0] = '>';
	vec[1] = IDSLAVE;
	vec[2] = ';';
	vec[3] = data;
	vec[4] = ';';

	aux[0] = IDSLAVE;
	aux[1] = data;

	chk = checkSum (aux, 2);

	vec[5] = chk;
	vec[6] = '<';
	sprintf (str, "%c%d%c%d%c%d%c", vec[0],vec[1],vec[2],vec[3],vec[4],vec[5],vec[6]);	//>id;data;chk<
	Display_lcd (str, 1 , 0);
	Transmitir (vec, 7);

//	data ++;
}

// +++ FUNCIONES PARA ANALIZAR TRAMA RECIBIDA +++
void Analize_MtoS (void)
{
	uint8_t caracter;
	static uint8_t i = 0;
	static uint8_t vecrx[5];
	static uint8_t vectemp[2];
	static uint8_t state = 0;
	uint8_t chk;
	char str[5];

	caracter = LeerBufferRX ();

	if (caracter != NO_KEY)
	{
		switch (state)
		{
			case 0:
				if (caracter == '>')
				{
					state = 1;
					vecrx[i] = caracter;
					i++;
				}
				else
				{
					state = 0;
					deleteDataPacket (vecrx, i);
					i = 0;
				}
				break;
			//Recibo ID Slave
			case 1:
				if (caracter>=0 && caracter<=255)
				{
					vectemp[0] = caracter;

					if (vectemp[0] == IDSLAVE)
					{
						state = 2;
						vecrx[i] = caracter;
						i++;
					}
					else
					{
						state = 0;
						deleteDataPacket (vecrx, i);
						i = 0;
					}
				}
				else
				{
					state = 0;
					deleteDataPacket (vecrx, i);
					i = 0;
				}
				break;
			case 2:
				if (caracter == ';')
				{
					state = 3;
					vecrx[i] = caracter;
					i++;
				}
				else
				{
					state = 0;
					deleteDataPacket (vecrx, i);
					i = 0;
				}
				break;
			//Recibo resultado del checksum
			case 3:
				if (caracter>=0 && caracter<=255)
				{
					vectemp[1] = caracter;
					chk = checkSum (vectemp, 2);
					//Verifico el checksum
					if (chk == 0)	//NO ERROR IN TRANSMISSION
					{
						state = 4;
						vecrx[i] = caracter;
						i++;
					}
					else			//ERROR DETECTED
					{
						state = 0;
						deleteDataPacket (vecrx, i);
						i = 0;
					}
				}
				else
				{
					state = 0;
					deleteDataPacket (vecrx, i);
					i = 0;
				}
				break;
			//Si pasa este check, ya tengo la vecrx armada y lista para enviar
			case 4:
				if (caracter == '<')
				{
					state = 0;

					vecrx[i] = caracter;
					sprintf (str, "%c%d%c%d%c", vecrx[0],vecrx[1],vecrx[2],vecrx[3],vecrx[4]);
					Display_lcd (str, 0 , 0);
					deleteDataPacket (vecrx, i);
					i = 0;
					rs485_flag = TX;
				}
				else
				{
					state = 0;
					deleteDataPacket (vecrx, i);
					i = 0;
				}
				break;

			default:
				deleteDataPacket (vecrx, i);
				i = 0;
		}
	}
}


// ********************************************** MASTER ********************************************** //
// +++ FUNCIONES PARA ARMAR TRAMA Y ENVIAR +++
void RS485_SendMtoS (uint8_t i)
{
	uint8_t vec[5];
	uint8_t chk;
	char str[6];

	vec[0] = '>';
	vec[1] = i;
	vec[2] = ';';
	chk = checkSum (&vec[1], 1);
	vec[3] = chk;
	vec[4] = '<';
	sprintf (str, "%c%d%c%d%c", vec[0],vec[1],vec[2],vec[3],vec[4]);	//>id;chk<
	Display_lcd (str, 0 , 0);
	Transmitir (vec, 5);
}

// +++ FUNCIONES PARA ANALIZAR TRAMAS RECIBIDAS +++
//Retorno 0 -> trama OK
//Retorno 1 -> checksum NOK
//Retorno 2 -> trama erronea/incompleta
uint8_t Analize_StoM (void)
{
	uint8_t caracter;
	static uint8_t i = 0;
	static uint8_t vecrx[7];
	static uint8_t vectemp[3];
	static uint8_t state = 0;
	uint8_t chk;
	char str[7];

	caracter = LeerBufferRX ();

	if (caracter != NO_KEY)
	{
		switch (state)
		{
			case 0:
				if (caracter == '>')
				{
					state = 1;
					vecrx[i] = caracter;
					i++;
				}
				else
				{
					state = 0;
					deleteDataPacket (vecrx, i);
					i = 0;
					return 2;
				}
				break;
			case 1:	//Recibo ID Slave
				if (caracter>=0 && caracter<=255)
				{
					state = 2;
					vecrx[i] = caracter;
					i++;
					vectemp[0] = caracter;
				}
				else
				{
					state = 0;
					deleteDataPacket (vecrx, i);
					i = 0;
					return 2;
				}
				break;
			case 2:
				if (caracter == ';')
				{
					state = 3;
					vecrx[i] = caracter;
					i++;
				}
				else
				{
					state = 0;
					deleteDataPacket (vecrx, i);
					i = 0;
					return 2;
				}
				break;
			case 3:	//Recibo data de medicion
				if (caracter>=0 && caracter<=255)
				{
					state = 4;
					vecrx[i] = caracter;
					i++;
					vectemp[1] = caracter ;
				}
				else
				{
					state = 0;
					deleteDataPacket (vecrx, i);
					i = 0;
					return 2;
				}
				break;
			case 4:
				if (caracter == ';')
				{
					state = 5;
					vecrx[i] = caracter;
					i++;
				}
				else
				{
					state = 0;
					deleteDataPacket (vecrx, i);
					i = 0;
					return 2;
				}
				break;
			case 5:	//Recibo resultado del checksum
				if (caracter>=0 && caracter<=255)
				{
					vectemp[2] = caracter;
					chk = checkSum (vectemp, 3);
					//Verifico el checksum
					if (chk == 0)	//NO ERROR IN TRANSMISSION
					{
						state = 6;
						vecrx[i] = caracter;
						i++;
					}
					else		//ERROR DETECTED, avanzo al siguiente estado para comprobar la trama completa y chequear si solo CHK NOK
					{
						state = 7;
						vecrx[i] = caracter;
						i++;
					}
				}
				else
				{
					state = 0;
					deleteDataPacket (vecrx, i);
					i = 0;
					return 2;
				}
				break;
			case 6:
				if (caracter == '<')			//Si pasa este check, ya tengo la vecrx armada y lista para enviar
				{
					state = 0;
					vecrx[i] = caracter;
					sprintf (str, "%c%d%c%d%c%d%c", vecrx[0],vecrx[1],vecrx[2],vecrx[3],vecrx[4],vecrx[5],vecrx[6]);
					//printf("%s\n", str);
					Display_lcd (str, 1 , 0);
					deleteDataPacket (vecrx, i);
					i = 0;
					return 0; //trama OK
				}
				else
				{
					state = 0;
					deleteDataPacket (vecrx, i);
					i = 0;
					return 2;
				}
				break;
			case 7:
				if (caracter == '<')			//Si pasa este check, ya tengo la vecrx armada pero el CHK NOK
				{
					state = 0;
					vecrx[i] = caracter;
					sprintf (str, "%c%d%c%d%c%d%c", vecrx[0],vecrx[1],vecrx[2],vecrx[3],vecrx[4],vecrx[5],vecrx[6]);
					//printf("%s\n", str);
					Display_lcd (str, 1 , 0);
					deleteDataPacket (vecrx, i);
					i = 0;
					return 1;
				}
				else
				{
					state = 0;
					deleteDataPacket (vecrx, i);
					i = 0;
					return 2;
				}
				break;

				default:
					deleteDataPacket (vecrx, i);
					i = 0;
					return 2;
		}
	}
	else
		return 2;
}


void RequestToSlave (void)
{
	static uint8_t state = 0;
	static uint8_t idslave = 0;
	static uint8_t repeat = 0;
	static uint32_t rs485_noframe = 0;
	uint8_t validate;


	switch (state)
	{
		case 0: //TRANSMITIR
			if (rs485_flag == TX)
			{
				gpio_set (RTS1, HIGH);			//RTS1 : P0[22] en 1 habilito TX
				RS485_SendMtoS (idslave);		//Envio trama
				rs485_flag = TXRX;
				state = 1;
			}
			break;
		case 1:
			if (rs485_flag == RX)
			{
				gpio_set (RTS1, LOW);
				validate = Analize_StoM ();

				if (validate == 0)			//La trama llego OK
				{
					//Display_lcd ("TRAMA OK", 1, 0);
					idslave ++;
					if (idslave > 5)
						idslave = 0;
					rs485_flag = RXTX;
					state = 0;
				}
				else if (validate == 1)		//CHK NOK, reintento hasta 3 veces en enviar/recibir trama del mismo slave
				{
					Display_lcd ("CHK NOK", 1, 0);
					repeat ++;
					if (repeat == 3)
					{
						repeat = 0;
						idslave ++;
						if (idslave > 5)
							idslave = 0;
					}
					rs485_flag = RXTX;
					state = 0;
				}
				else
				{
					rs485_noframe ++;
					if (rs485_noframe >= 10000)
					{
						rs485_noframe = 0;
						idslave ++;
						if (idslave > 5)
							idslave = 0;
						rs485_flag = RXTX;
						state = 0;
					}
				}

				break;
		default:
			rs485_flag = RXTX;
			state = 0;
			}
	}
}

// +++ FUNCION CHECKSUM +++
uint8_t checkSum (uint8_t *v, uint8_t t)
{
 	uint8_t chksum=0, i;

    //printf("\n****SENDER****\n");
	for(i=0; i<t; i++)
      	chksum ^= v[i];
    return chksum;
}

// +++ FUNCION LIMPIAR VECTOR +++
void deleteDataPacket (uint8_t *v, uint8_t i)
{
	uint8_t j;

	for (j=0; j<i; j++)
		v[j] = 0;
}
