/*****************************************************************************
*
* Atmel Corporation
*
* File              : spi.c
* Compiler          : IAR EWAAVR 2.28a/3.10c
* Revision          : $Revision: 1.3 $
* Date              : $Date: 17. mars 2004 14:47:10 $
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
// Description      : Based on example code from Mega8 data sheet
****************************************************************************/

#include "allheaders.h"

void SPI_MasterInit(void)
{
  // Set MOSI, SCK and SS output, all others input
  DDR_SPI = (1 << P_MOSI) | (1 << P_SCK) | (1 << P_SS);
  // make SS output high
  PORT_SPI |= (1 << P_SS); 
  // Enable SPI, Master, set clock rate fck/16
  SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);
}

char SPI_MasterTransmit(char cData)
{
  // Start transmission
  SPDR = cData;
  // Wait for transmission complete
  while(!(SPSR & (1 << SPIF)));
  return (SPDR);
}
