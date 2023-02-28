#ifndef LED_H
#define LED_H
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

void led_init(void);
void led_on(void);
void led_off(void);
void blink(void);


#endif 