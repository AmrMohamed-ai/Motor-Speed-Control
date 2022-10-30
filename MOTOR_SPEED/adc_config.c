/******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.c
 *
 * Description: Source file for the ATmega16 ADC driver
 *
 * Author: Mohamed Tarek
 *
 *******************************************************************************/

#include "adc_config.h"
/*******************************************************************************
 *                          Global Variables                                   *
 *******************************************************************************/

volatile uint16 g_adcResult = 0;

/*******************************************************************************
 *                          ISR's Definitions                                  *
 *******************************************************************************/

ISR(ADC_vect)
{
	if(g_callBackPtr != NULL_PTR)
		{
			(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr_OVF(); */
		}
}


/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
void ADC_setCallBack(void(*a_ptr)(void))
{
	g_callBackPtr = a_ptr;
}

void ADC_init(const ADC_ConfigType *Config_Ptr)
{
    uint8 VREFF , TRIGGER;

    VREFF = Config_Ptr->vref;
    TRIGGER = Config_Ptr->trigger;
	ADC_CRL_STATUS_REG_A |= (1<<ADEN);
	if( Config_Ptr-> mode == INTERRUPT )
	{
		if( BIT_IS_CLEAR(SREG, 7) ) SET_BIT( SREG, 7 );
		ADC_CRL_STATUS_REG_A |= (1<<ADIE);

	}


	ADC_MUX_SEL_REG = ( ADC_MUX_SEL_REG & 0x3F) | ( ROR( VREFF ,2) ) ;

	if(Config_Ptr ->trigger != FREE_RUNNING)
	{
		SET_BIT(ADC_CRL_STATUS_REG_A, 5);
		ADC_FUNC_REG = ( ADC_FUNC_REG & 0x1F) | (  ROR(TRIGGER ,3) );
	}

	ADC_MUX_SEL_REG = ( ADC_MUX_SEL_REG & 0xF8) | ( Config_Ptr-> prescaler) ;

	if(Config_Ptr ->adjust == LEFT_ADJUST)
	{
		SET_BIT(ADC_MUX_SEL_REG,5);
	}
}


//void ADC_init(void)
//{
//	/* ADMUX Register Bits Description:
//	 * REFS1:0 = 00 to choose to connect external reference voltage by input this voltage through AREF pin
//	 * ADLAR   = 0 right adjusted
//	 * MUX4:0  = 00000 to choose channel 0 as initialization
//	 */
//	ADMUX = 0;
//
//	/* ADCSRA Register Bits Description:
//	 * ADEN    = 1 Enable ADC
//	 * ADIE    = 0 Disable ADC Interrupt
//	 * ADPS2:0 = 011 to choose ADC_Clock=F_CPU/8=1Mhz/8=125Khz --> ADC must operate in range 50-200Khz
//	 */
//	ADCSRA = (1<<ADEN) | (1<<ADPS1) | (1<<ADPS0);
//}

uint16 ADC_readChannel(uint8 channel_num, const ADC_ConfigType *Config_Ptr)
{
	channel_num &= 0x07; /* channel number must be from 0 --> 7 */
	ADMUX &= 0xE0; /* clear first 5 bits in the ADMUX (channel number MUX4:0 bits) before set the required channel */
	ADMUX = ADMUX | channel_num; /* choose the correct channel by setting the channel number in MUX4:0 bits */
	SET_BIT(ADCSRA,ADSC); /* start conversion write '1' to ADSC */
	if(Config_Ptr -> mode == POLLING)
	{
		while(BIT_IS_CLEAR(ADCSRA,ADIF)); /* wait for conversion to complete ADIF becomes '1' */
		SET_BIT(ADCSRA,ADIF); /* clear ADIF by write '1' to it :) */
		return ADC; /* return the data register */
	}
	return 0;
}
