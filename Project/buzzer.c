#include "buzzer.h"

 
void buzzer_init(void)
{
  
        GPIOUnlockPin(GPIO_PORTA_BASE , GPIO_PIN_6);
        
	GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE , GPIO_PIN_6 );

	GPIOPinWrite (GPIO_PORTA_BASE , GPIO_PIN_6 , 0x00);
}


  
 
 
void buzzer_on(void)
{
	GPIOPinWrite (GPIO_PORTA_BASE , GPIO_PIN_6 , GPIO_PIN_6);
}



  
 
 
void buzzer_off(void)
{
	GPIOPinWrite (GPIO_PORTA_BASE , GPIO_PIN_6,0x00);
}
void buzzer_timeout()
{
  buzzer_on();
  SysCtlDelay(8000000);
  buzzer_off();
  SysCtlDelay(8000000);
    buzzer_on();
  SysCtlDelay(8000000);
  buzzer_off();
  SysCtlDelay(8000000);
    buzzer_on();
  SysCtlDelay(8000000);
  buzzer_off();
  SysCtlDelay(8000000);
  
  
  
}