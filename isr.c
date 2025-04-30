/*
 * File:   isr.c
 * Author: vaibh
 *
 * Created on 26 November, 2024, 3:46 PM
 */

#include "header_server.h"

extern unsigned char ch;

void __interrupt() isr(void)
{
    if (RCIF==1)
    {
        if (OERR==1)
            OERR=0;
        
        ch= RCREG;
        
        RCIF=0;
    }

}
