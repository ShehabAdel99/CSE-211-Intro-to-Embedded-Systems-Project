#ifndef STOPWATCH_H
#define STOPWATCH_H
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
void start(void);
void reset(void);
void pause(void);
void displayTime(void);
void PORTA_handler(void);

#endif
