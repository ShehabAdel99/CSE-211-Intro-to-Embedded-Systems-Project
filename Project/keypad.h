#ifndef keypad_H
#define keypad_H
#include "tm4c123gh6pm.h"
#include "types.h"
#include "bitwise_operation.h"
#include <stdbool.h>
#include <stdint.h>
#include "driverlib/sysctl.h"
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"


void keypad_init(void);
char  keypad_read(void);

#endif