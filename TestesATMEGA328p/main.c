/*
 * TestesATMEGA328p.c
 *
 * Created: 29/10/2019 17:30:29
 * Author : ricar
 */ 

#define F_CPU 8000000UL
#define BAUD 115200
#define MYUBRR ((F_CPU/16/BAUD)-1)

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include "functions.h"
#include "adc_to_temp.h"

volatile uint8_t count=0;

ISR(TIMER0_COMPB_vect)
{
	count++;
}



int main(void)
{
    /* Replace with your application code */
    pinConfig();
	timerConfig();
	USART_Init(MYUBRR);	
	setPWM();
	//setDC(50.25);
	adc_setup();
	sei();
	SEGA_ON; SEGB_ON; SEGC_ON; SEGD_ON; SEGE_ON ; SEGF_ON; 
	SEGG_OFF; DP_OFF; 
	DISP1_OFF; DISP2_OFF; DISP3_OFF;
	while (1) 
    {
		//floatoa_(5);
		//intoa_(5);
		//printToSerialPort();
		if(count == 100)
		{
			USART_Transmit('F');
			count=0;
		}	
		//_delay_ms(500);
	}
}



