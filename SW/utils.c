#include "utils.h"
#include "distance_sensor.h"

void print_welcome_message(void)
{
	LCD1602_ClearAll();					
	LCD1602_Print("Final project");		
	LCD1602_SetCursor(0,1);			
	LCD1602_Print("for TMP classes");
	delay_ms(2 * DISPLAY_PERIOD);
	
	LCD1602_ClearAll();					
	LCD1602_Print("Distance meter");		
	LCD1602_SetCursor(0,1);			
	LCD1602_Print("using HC-SR04");
	delay_ms(2 * DISPLAY_PERIOD);
	
	LCD1602_ClearAll();					
	LCD1602_Print("Created by");		
	LCD1602_SetCursor(0,1);			
	LCD1602_Print("Pawel Tymoczko");
	delay_ms(2 * DISPLAY_PERIOD);
	
	LCD1602_ClearAll();					
	LCD1602_Print("Press S1 button");		
	LCD1602_SetCursor(0,1);			
	LCD1602_Print("to continue");
}

void print_enable_message(void)
{
	LCD1602_ClearAll();	
	LCD1602_Print("Distance meter");
	LCD1602_SetCursor(0,1);
	LCD1602_Print("enabled");
	delay_ms(0.5 * DISPLAY_PERIOD);
	LCD1602_ClearAll();	
	LCD1602_SetCursor(0,0);
}

void print_disable_message(void)
{
	LCD1602_ClearAll();	
	LCD1602_Print("Press S2 to");
	LCD1602_SetCursor(0,1);
	LCD1602_Print("disable/enable");
	delay_ms(DISPLAY_PERIOD);
	LCD1602_ClearAll();	
	LCD1602_SetCursor(0,0);
}

void print_distance(char* display, int distance)
{
		sprintf(display, "Dist [m]  %d", distance);
		LCD1602_SetCursor(0,0);
		LCD1602_Print(display);
		LCD1602_SetCursor(0,1);
		sprintf(display, "Dist [in] %d", cm2inches(distance));
		LCD1602_Print(display);
		delay_ms(DISPLAY_PERIOD);
		LCD1602_ClearAll();
}

int cm2inches(int distance)
{
	return distance != OUT_OF_RANGE ? distance * CM_TO_INCH_FACTOR : OUT_OF_RANGE;
}
