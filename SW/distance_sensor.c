#include "distance_sensor.h"

/* Global variables for counting time on ECHO_Pin */
static uint16_t old_ctr = 0;
static uint16_t new_ctr = 0;
static uint16_t ctr_diff = 0;

/* Generate a 10us impuls on TRIG_Pin */
void generate_TRIG_inpulse(void)
{
	PTB->PTOR |= TRIG_MASK;
	delay_us(10);
	PTB->PTOR |= TRIG_MASK;
}

/* Initializing TRIG_Pin as GPIO output*/
void TRIG_Init(void)
{
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK; /* Connect PORTB to clock*/
  PORTB->PCR[TRIG_Pin] = PORT_PCR_MUX(1); /* Set TRIG_Pin as GPIO pin */
  PTB->PDDR |= TRIG_MASK; /* Set TRIG_Pin as output*/
	PTB->PSOR |= TRIG_MASK; /* Set TRIG_Pin */
}

/* TPM1 interrupt handler */
/* Used in order to count time between transmiting and receiving sound wave on ECHO_Pin */
void TPM1_IRQHandler(void)
{
	old_ctr = new_ctr;
	new_ctr = TPM1->CONTROLS[1].CnV & 0xFFFFFFFF; /* Mask to get only 32bits */
	ctr_diff = new_ctr - old_ctr;
	TPM1->CONTROLS[1].CnSC |= TPM_CnSC_CHF_MASK; /* Clear interrupt flag, allow new interrupt*/
}

/* Initializing TPM1 channel 3*/
void TPM1_InputCapture_Init(void)
{
	SIM->SCGC6 |= SIM_SCGC6_TPM1_MASK;		/* Enable clock for TPM1 */
	SIM->SOPT2 |= SIM_SOPT2_TPMSRC(1);		/* Choosing MCGFLLCLK as a source for TPM1 */
	
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK; 	/* Connecting clock to PORTB */
	PORTB->PCR[ECHO_Pin] = PORT_PCR_MUX(2);   /* Choose ECHO_Pin as TPM */
	
	TPM1->SC |= TPM_SC_PS(7);  						/* Set prescaler as 2^7 = 128 */
	TPM1->SC |= TPM_SC_CMOD(1);						/* Select the internal input clock source for TPM1 */
	
  /* "input capture" mode */
	TPM1->SC &= ~TPM_SC_CPWMS_MASK; 		/* Set up-counting mode */
	TPM1->CONTROLS[1].CnSC |= (TPM_CnSC_ELSB_MASK | TPM_CnSC_ELSA_MASK | TPM_CnSC_CHIE_MASK); /* set input capture on both edges and enable interrupt on chanel 3 */
	
	NVIC_SetPriority(TPM1_IRQn, 1);  /* Set TPM0 interrupt priority level */   
	NVIC_ClearPendingIRQ(TPM1_IRQn); /* Clear pending interrupts */
	NVIC_EnableIRQ(TPM1_IRQn);			 /* Enable TPM1 Interrupts */ 
}

/* Calculate distance based on counted value */
uint32_t get_distance(void)
{
	uint32_t ret = ctr_diff / DISTANCE_FACTOR;
	return ret > MIN_RANGE_IN_CM && ret < MAX_RANGE_IN_CM ? ret : OUT_OF_RANGE;
}
