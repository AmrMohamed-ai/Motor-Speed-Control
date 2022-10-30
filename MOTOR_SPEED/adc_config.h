/******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.h
 *
 * Description: header file for the ATmega16 ADC driver
 *
 * Author: Amr Mohamed
 *
 *******************************************************************************/

#ifndef ADC_CONFIG_H_
#define ADC_CONFIG_H_

#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"
/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_callBackPtr)(void) = NULL_PTR;


/*********************************************************************************
 * 							ADC REGISTERS                                        *
 ********************************************************************************/
#define ADC_MUX_SEL_REG				ADMUX
#define ADC_CRL_STATUS_REG_A        ADCSRA
#define ADC_DATA_REG                ADC
#define ADC_FUNC_REG                SFIOR
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
typedef enum
{
	EXTERNAL_REF, AVCC_EX_CAP, RESERVED, INTERNAL_2d56v_EX_CAP
}ADC_refrenceSelection;

typedef enum
{
	FREE_RUNNING, ANALOG_COMPARATOR, INT_0, TIMER_0_CMP, TIMER_0_OVF, TIMER_1_CMP_B, TIMER_1_OVF, TIMER_1_CE
}ADC_autoTrigger;

typedef enum
{
	POLLING, INTERRUPT
}ADC_mode;

typedef enum
{
	_2, _4, _8, _16, _32, _64, _128
}ADC_Prescaler;

typedef enum
{
	LEFT_ADJUST, RIGHT_ADJUST
}ADC_resultAdjust;


typedef struct
{
	ADC_refrenceSelection vref;
	ADC_autoTrigger trigger;
	ADC_mode mode;
	ADC_Prescaler prescaler;
	ADC_resultAdjust adjust;
}ADC_ConfigType;

/*
 * Description :
 * Function responsible for initialize the ADC driver.
 */
void ADC_init(const ADC_ConfigType * Config_Ptr);

/*
 * Description :
 * Function responsible for read analog data from a certain ADC channel
 * and convert it to digital using the ADC driver.
 */
uint16 ADC_readChannel(uint8 channel_num, const ADC_ConfigType *Config_Ptr);

void ADC_setCallBack(void(*a_ptr)(void));

#endif /* ADC_CONFIG_H_ */
