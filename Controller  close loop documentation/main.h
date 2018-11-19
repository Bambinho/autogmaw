/*****************************************************************************
*
* Atmel Corporation
*
* File              : main.h
* Compiler          : IAR EWAAVR 2.28a/3.10c
* Revision          : $Revision: 1.3 $
* Date              : $Date: 17. mars 2004 14:47:32 $
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
// Platform         : Developed on STK500. Can be used stand-alone.
// Description      : Header file for main.c
****************************************************************************/

#define MAXSEQ        16 // maximum number of bytes for extended sequence,
                         // 16 limit set to keep terminal display tidy.
#define MAXSTATSTRLEN 11 // maximum status string length
#define MAXHELPSTRLEN 64 // maximum help string length
#define MAXFREQSTRLEN 40 // maximum frequency string length
#define STATLONG      0  // identifier for single line status display
#define STATLIST      1  // identifier for detailed list status display

// prototypes
void send_str (const char __flash *);
char getnextchar(void);
char htoa (char);
void spi_tx (char);
void showhelp(void);
void showstatus(char);
void hexsequence(void);
void setfreq(void);
void setsspin(void);
void sspinadjust(char);
void setautomode(void);
void setorder(void);
void setmode(void);
void writeconfig(void);
void loadconfig(void);

