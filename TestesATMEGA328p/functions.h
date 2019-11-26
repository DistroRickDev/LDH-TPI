/*
 * functions.h
 *
 * Created: 05/11/2019 21:14:37
 *  Author: ricar
 */ 


#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#define DP_OFF (PORTC|=(1<<PORTC2))
#define SEGG_OFF (PORTC|=(1<<PORTC3))
#define SEGF_OFF (PORTC|=(1<<PORTC4))
#define SEGE_OFF (PORTC|=(1<<PORTC5))
#define SEGA_OFF (PORTD|=(1<<PORTD2))
#define SEGB_OFF (PORTD|=(1<<PORTD3))
#define SEGC_OFF (PORTD|=(1<<PORTD4))
#define SEGD_OFF (PORTD|=(1<<PORTD5))

#define DP_ON (PORTC&=~(1<<PORTC2))
#define SEGG_ON (PORTC&=~(1<<PORTC3))
#define SEGF_ON (PORTC&=~(1<<PORTC4))
#define SEGE_ON (PORTC&=~(1<<PORTC5))
#define SEGA_ON (PORTD&=~(1<<PORTD2))
#define SEGB_ON (PORTD&=~(1<<PORTD3))
#define SEGC_ON (PORTD&=~(1<<PORTD4))
#define SEGD_ON (PORTD&=~(1<<PORTD5))

#define LEDN_ON (PORTB&=~(1<<PORTB7) && SEGA_ON)
#define LEDC_ON	(PORTB&=~(1<<PORTB7) && SEGB_ON)
#define LEDF_ON (PORTB&=~(1<<PORTB7) && SEGC_ON)

#define LEDN_OFF ((PORTB|=(1<<PORTB7)) && SEGA_OFF)
#define LEDC_OFF ((PORTB|=(1<<PORTB7)) && SEGB_OFF)
#define LEDF_OFF ((PORTB|=(1<<PORTB7)) && SEGC_OFF)

#define DISP1_OFF (PORTD|=(1<<PORTD6))
#define DISP3_OFF (PORTD|=(1<<PORTD7))
#define DISP2_OFF (PORTB|=(1<<PORTB0))


#define DISP1 (PORTD&=~(1<<PORTD6))
#define DISP3 (PORTD&=~(1<<PORTD7))
#define DISP2 (PORTB&=~(1<<PORTB0))


#define DELAY(x) _delay_ms(x*1000)


void pinConfig();
void timerConfig();
void setPWM(); //function responsible to setup PWM
void setDC(float perc);
unsigned char USART_Receive( void );
void USART_Transmit( unsigned char data );
void USART_Init( unsigned int ubrr);
void adc_setup();
void intoa_(int val);
void floatoa_(int val);
void printToSerialPort();

#endif /* FUNCTIONS_H_ */