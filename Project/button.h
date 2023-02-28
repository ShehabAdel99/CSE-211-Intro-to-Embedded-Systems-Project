#ifndef Button_H
#define Button_H
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

void button0_init(void);
void button1_init(void);
void button2_init(void);
void buttons_init(void);







#endif