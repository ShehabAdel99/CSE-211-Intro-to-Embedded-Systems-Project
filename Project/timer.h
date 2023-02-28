#ifndef Timer_H
#define Timer_H
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"
#include "driverlib/sysctl.h"
#include "lcd.h"
#include "keypad.h"
void timer_start(void);
void timer0A_ISR(void);
void diplay_timer(void);
void timer_reset(void);
void timeout(void);





#endif