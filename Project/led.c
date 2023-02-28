#include "led.h"

 
void led_init(void)
{
  
        GPIOUnlockPin(GPIO_PORTA_BASE , GPIO_PIN_5);
        
	GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE , GPIO_PIN_5 );

	GPIOPinWrite (GPIO_PORTA_BASE , GPIO_PIN_5 , 0x00);
}


  
 
 
void led_on(void)
{
	GPIOPinWrite (GPIO_PORTA_BASE , GPIO_PIN_5 , GPIO_PIN_5);
}



  
 
 
void led_off(void)
{
	GPIOPinWrite (GPIO_PORTA_BASE , GPIO_PIN_5,0x00);
}
void blink()
{
  led_on();
  SysCtlDelay(8000000);
  led_off();
  SysCtlDelay(8000000);
    led_on();
  SysCtlDelay(8000000);
  led_off();
  SysCtlDelay(8000000);
    led_on();
  SysCtlDelay(8000000);
  led_off();
  SysCtlDelay(8000000);
  
}