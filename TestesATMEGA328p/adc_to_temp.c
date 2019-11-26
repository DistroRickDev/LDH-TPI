/*
*
*/ 
#define F_CPU 8000000UL
#include <avr/io.h>
#include "adc_to_temp.h"


float conversionToVoltage()
{
	return  (float)(ADC * 0.00488);
}