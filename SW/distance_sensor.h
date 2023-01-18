#ifndef DISTANCE_SENSOR_H
#define DISTANCE_SENSOR_H

#include "MKL05Z4.h"
#include "frdm_bsp.h"
#include "lcd1602.h"
#include "klaw.h"
#include "delay.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ECHO_Pin 				(13)
#define TRIG_Pin				(5)

#define ECHO_MASK				(1 << ECHO_Pin)
#define TRIG_MASK				(1 << TRIG_Pin)

#define DISTANCE_FACTOR	(19)
#define MIN_RANGE_IN_CM (2)
#define MAX_RANGE_IN_CM	(200)
#define OUT_OF_RANGE		(9999)

void HC_SR05_Init(void);

void TRIG_Init(void);

void TPM1_IRQHandler(void);

void TPM1_InputCapture_Init(void);

void generate_TRIG_inpulse(void);

uint32_t get_distance(void);

#endif
