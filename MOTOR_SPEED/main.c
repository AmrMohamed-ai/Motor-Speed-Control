/*
 * speed.c
 *
 *  Created on: Aug 8, 2022
 *      Author: Amr Mohamed
 */

#include "motor.h"
#include "lcd.h"
#include "adc_config.h"
#include "timer0_config.h"
#include "common_macros.h"
#include "std_types.h"
#include "micro_config.h"

void INT1_init( void )
{
	GICR  |= ( 1<<INT1 ) ;                   // enable interrupt 0
	MCUCR |= ( 1<<ISC11 ) | ( 1<<ISC10 ) ;   // interrupt request at rising edge
	DDRD  &= ~( 1<<PD3 ) ;                   // configure pin 3 in PORTD as input pin
}

void INT0_init( void )
{
	GICR  |= ( 1<<INT0 ) ;                   // enable interrupt 0
	MCUCR |= ( 1<<ISC01 )|(1<<ISC00)  ;   // interrupt request at rising edge
	DDRD  &= ~( 1<<PD2 ) ;                   // configure pin 3 in PORTD as input pin
}

ISR(INT1_vect)
{
	MOTOR_reverse();
}

ISR(INT0_vect)
{
	MOTOR_ON_OFF();
}


int main(void)
{
	SREG|= (1<<7);
	INT1_init();
	INT0_init();
	uint16 comp_value;
	uint16 res_value;
	ADC_ConfigType ADC_config = {EXTERNAL_REF, FREE_RUNNING, POLLING, _8, RIGHT_ADJUST};
	Timer0_ConfigType Timer0_config = {PWM_MODE, 0, F_CPU_8, 0, 128  };
	ADC_init(&ADC_config);
	Timer0_init(&Timer0_config);
	MOTOR_init();
	MOTOR_start();
	LCD_init();
	LCD_clearScreen();
	LCD_displayString("ADC Value = ");


	while(1)
	{
		res_value = ADC_readChannel(0, &ADC_config) ;
		comp_value = res_value /4;
		Timer0_config.DutyCycle = comp_value;
		Timer0_init(&Timer0_config);
		LCD_goToRowColumn(0,12); /* display the number every time at this position */
		LCD_intgerToString(res_value); /* display the ADC value on LCD screen */
	}


}



