#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include "functions.h"
#include "adc_to_temp.h"

char value[10];

void pinConfig()
{
	/*       76543210*/
	DDRB = 0b10000111;
	DDRC = 0b00111100;
	DDRD = 0b11111110;
}



void timerConfig()
{
	TCCR0A |=(1<<WGM01); //clear on compare
	TCCR0B |=(1<<CS02);//prescaler 256
	TIMSK0 |=(1<<OCIE0B);
	TCNT0 =0;
	/* fOC0 = (F_CPU/(2*N*(1+OCR0A)) N = (1,8,64,256,1024) */
	OCR0B = 155; //to generate a 100Hz frequency, 10ms period	
}

void setPWM()
{
	TCCR1A |= (1<<COM1A1)|(1<<WGM11); //Register modified to have fast PWM
	
	TCCR1B |= (1<<WGM12) |(1<<WGM13)|(1<<CS10); //Register modified to have no PRESCALER and having ICR1 has top value
	
	ICR1 = 799; /*PWM_FREQUENCY = F_CPU/N*(1+TOP) PWM CALCULATED FOR 50HZ*/
}

void setDC(float perc)
{
	float DC =  (((float)ICR1/(float)100.0) *  perc);
	OCR1A = (uint16_t) DC;
}

void USART_Transmit( unsigned char data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) );
	/* Put data into buffer, sends the data */
	UDR0 = data;
}

void USART_Init( unsigned int ubrr)
{ // function responsible to set up RX and TX communication
	/*Set baud rate */
	UBRR0H = (unsigned char)(ubrr>>8); //sets the baud rate value
	UBRR0L = (unsigned char)ubrr;
	/*Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0)|(1<<TXCIE0); // register enables RX and TX and also their respective interrupts
	/* Set frame format: 8data, 1stop bit */
	UCSR0C = (0<<USBS0)|(3<<UCSZ00);
}

void adc_setup()
{
	ADMUX |= (1<<REFS0)|(0<<REFS1);//Enables VCC as ref voltage also selects ADC2 analog channel
	
	ADCSRA |= (1<<ADEN)|(1<<ADSC)|(1<<ADATE)|(1<<ADIE)|(1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2); //enables ADC, starts conversion, auto trigger enabled, ADC presacler set to 128
	
	ADCSRB |= (0<<ADTS0)|(0<<ADTS1)|(0<<ADTS2); // trigger set for free running mode
}

void intoa_(int val){
	for(int i=0; i<5; i++)
	{
		value[i] = ' ';
	}
	sprintf(value, "%d", ADC);
}

void floatoa_(int val)
{
	float values = conversionToVoltage();
	int unit = (int)values;
	int dec = (values*10000) -(unit*10000);
	for(int i=0; i<5; i++)
	{
		value[i] = ' ';
	}
	sprintf(value, "%d.%d v", unit, dec);
}


void printToSerialPort()
{
	for(int i=0; value[i]!='\0'; i++){
		USART_Transmit(value[i]);
	}
	USART_Transmit('\n');
}