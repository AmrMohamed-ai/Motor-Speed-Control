/*
 * motor.c
 *
 *  Created on: Aug 8, 2022
 *      Author: Amr Mohamed
 */



#include"motor.h"


void MOTOR_init()
{
	SET_BIT(DDRB, IN1);
	SET_BIT(DDRB, IN2);

}

void MOTOR_ON_OFF()
{
	if(BIT_IS_SET(PORTB, IN1) || BIT_IS_SET(PORTB, IN2) )
	{
		MOTOR_stop();
	}
	else
	{
		MOTOR_start();
	}
}


void MOTOR_start()
{
	SET_BIT(PORTB, IN1);
	CLEAR_BIT(PORTB, IN2);
}


void MOTOR_stop()
{
	CLEAR_BIT(PORTB, IN1);
	CLEAR_BIT(PORTB, IN2);
}

void MOTOR_reverse()
{
	TOGGLE_BIT(PORTB, IN1);
	TOGGLE_BIT(PORTB, IN2);

}
