
/*****************************************************************************
*
* Atmel Corporation
*
* File              : spi.h
* Compiler          : IAR EWAAVR 2.28a/3.10c
* Revision          : $Revision: 1.3 $
* Date              : $Date: 17. mars 2004 14:47:28 $
* Updated by        : $Author: ltwa $
*
* Support mail      : avr@atmel.com
*
* Supported devices : All devices with a SPI and USART module can be used.
*                     The example is written for the ATmega8
*
* AppNote           : AVR303 - SPI-UART Gateway
*
// Author           : Andy Gayne. avr@gayne.co.uk   www.gd-technik.com
// Description      : Header file for spi.c
****************************************************************************/

#define DDR_SPI   DDRB
#define PORT_SPI  PORTB
#define P_SS      PB2
#define P_MOSI    PB3
#define P_SCK     PB5

void SPI_MasterInit(void);
char SPI_MasterTransmit(char);
