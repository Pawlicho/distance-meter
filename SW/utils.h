#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "MKL05Z4.h"
#include "frdm_bsp.h"
#include "lcd1602.h"
#include "delay.h"

#define DISPLAY_PERIOD (1000)
#define CM_TO_INCH_FACTOR (0.393700787)

void print_welcome_message(void);
void print_enable_message(void);
void print_disable_message(void);
void print_distance(char* display, int distance);

int cm2inches(int distance);

#endif
