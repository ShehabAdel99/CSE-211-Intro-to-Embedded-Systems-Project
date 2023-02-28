#include "button.h"
#include "Stopwatch.h"



// initialize PORTA pin 2 as an input pin for the stopwatch start external switch
void button0_init() //pin 2 Start   
{
    //Enable clock gating for the port
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA));
    
    // Configure the pin as an input pin
    GPIOUnlockPin(GPIO_PORTA_BASE, GPIO_PIN_2);
    GPIOPinTypeGPIOInput(GPIO_PORTA_BASE, GPIO_PIN_2);
    
    //Enable pin interrups
    GPIOIntEnable(GPIO_PORTA_BASE, GPIO_INT_PIN_2); 
    GPIOIntTypeSet(GPIO_PORTA_BASE, GPIO_PIN_2, GPIO_FALLING_EDGE); 
    GPIOIntRegister(GPIO_PORTA_BASE,PORTA_handler);
}


// initialize PORTA pin 3 as an input pin for the stopwatch pause external switch
void button1_init() //pin 3 Pause
{
    //Enable clock gating for the port
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA));
    
    // Configure the pin as an input pin
    GPIOUnlockPin(GPIO_PORTA_BASE, GPIO_PIN_3);
    GPIOPinTypeGPIOInput(GPIO_PORTA_BASE, GPIO_PIN_3);
    
    //Enable pin interrups
    GPIOIntEnable(GPIO_PORTA_BASE, GPIO_INT_PIN_3); 
    GPIOIntTypeSet(GPIO_PORTA_BASE, GPIO_PIN_3, GPIO_FALLING_EDGE); 

}

// initialize PORTA pin 4 as an input pin for the stopwatch reset external switch
void button2_init() //pin 4 reset
{
    //Enable pin interrups
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA));
    
    // Configure the pin as an input pin
    GPIOUnlockPin(GPIO_PORTA_BASE, GPIO_PIN_4);
    GPIOPinTypeGPIOInput(GPIO_PORTA_BASE, GPIO_PIN_4);
    
    //Enable pin interrups
    GPIOIntEnable(GPIO_PORTA_BASE, GPIO_INT_PIN_4); 
    GPIOIntTypeSet(GPIO_PORTA_BASE, GPIO_PIN_4, GPIO_FALLING_EDGE); 
}

  
  
 

