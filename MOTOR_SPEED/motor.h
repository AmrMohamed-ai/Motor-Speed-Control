/*
 * motor.h
 *
 *  Created on: Aug 8, 2022
 *      Author: Amr Mohamed
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#include"common_macros.h"
#include"micro_config.h"
#include"std_types.h"


#define IN1     PB2
#define IN2     PB1
#define EN1     PB3


void MOTOR_init(void);

void MOTOR_start(void);

void MOTOR_ON_OFF(void);

void MOTOR_stop(void);

void MOTOR_reverse(void);


#endif /* MOTOR_H_ */
