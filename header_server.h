/* 
 * File:   header_server.h
 * Author: DELL
 *
 * Created on March 19, 2025, 2:58 PM
 */

#ifndef HEADER_SERVER_H
#define	HEADER_SERVER_H

#include <xc.h>
#include "can.h"

#define _XTAL_FREQ 20000000

/* Defines the data */
#define TRUE			1
#define FALSE			0

//UART
#define RX_PIN					TRISC7
#define TX_PIN					TRISC6

#define SLAVE_READ		0xD1
#define SLAVE_WRITE		0xD0

typedef enum {
    recv,transmit
} Mode;


extern Mode mode; 

extern unsigned char u[5];
extern unsigned char p[5];
void init_config();

void init_uart(void);
void putch(unsigned char byte);
int puts(const char *s);
unsigned char getch(void);
unsigned char getch_with_timeout(unsigned short max_time);
unsigned char getche(void);

void recv_data();
void trans_data();


unsigned char ch;


#endif	/* HEADER_SERVER_H */

