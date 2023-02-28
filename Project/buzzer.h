#ifndef BUZZ_H
#define BUZZ_H
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

void buzzer_init(void);
void buzzer_on(void);
void buzzer_off(void);
void buzzer_timeout(void);


#endif 