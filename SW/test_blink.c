#include "MKL05Z4.h"
#include "frdm_bsp.h"
#include "lcd1602.h"
#include "klaw.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "distance_sensor.h"
#include "utils.h"

/* Variables indicating if button is pressed */
volatile uint8_t S2_press=0;
volatile uint8_t S3_press=0;
volatile uint8_t S4_press=0;

/* Button interrupt handler */
void PORTA_IRQHandler(void)
{
	uint32_t buf;
	buf=PORTA->ISFR & (S2_MASK | S3_MASK | S4_MASK);

	switch(buf)
	{
		case S2_MASK:	DELAY(10)
			if(!(PTA->PDIR&S2_MASK))
			{
				if(!(PTA->PDIR&S2_MASK))
				{
					S2_press=1;
				}
			}
			break;
		case S3_MASK:	DELAY(10)
			if(!(PTA->PDIR&S3_MASK))
			{
				if(!(PTA->PDIR&S3_MASK))
				{
					if(!S3_press)
					{
						S3_press=1;
					}
				}
			}
			break;
		case S4_MASK:	DELAY(10)
			if(!(PTA->PDIR&S4_MASK))
			{
				if(!(PTA->PDIR&S4_MASK))
				{
					if(!S4_press)
					{
						S4_press=1;
					}
				}
			}
			break;
		default:	break;
	}	
	
	PORTA->ISFR |=  S2_MASK | S3_MASK | S4_MASK; /* Clear ISF bits */
	NVIC_ClearPendingIRQ(PORTA_IRQn); /* Clear pending interrupts */
}

int main(void)
{
	
	char display[]={0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20};
	volatile int distance = 0;
	volatile uint8_t distance_meter_enable = 0;
	
	Klaw_Init();								/* Initialization of button matrix */
	Klaw_S2_4_Int();						/* S2, S3, S4 are set as source of interrupts */
	
	LCD1602_Init();		 					/* LCD1602 initialization */
	LCD1602_Backlight(TRUE);
	
	TRIG_Init();								/* TRIG_Pin initialization */
	TPM1_InputCapture_Init();		/* TPM1 initialization */
	
	print_welcome_message();
	
	while(PTA->PDIR&S1_MASK);
	
	print_disable_message();
	
	while (1)
	{
		if(S2_press)
		{
			distance_meter_enable ^= 0x01;
			S2_press = 0;
		}
		if(S3_press)
		{
			S3_press = 0;
		}
		if(S4_press)
		{

			S4_press = 0;
		}
		
		if (distance_meter_enable)
		{
			generate_TRIG_inpulse();
			distance = get_distance();
			print_distance(display, distance);
		}
		else
		{
			print_disable_message();
		}
		
	}

}
