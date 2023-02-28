#include <stdbool.h>
#include <stdint.h>
#include "lcd.h"
#include "keypad.h"
#include "driverlib/sysctl.h"
#include <stdio.h>
#include "calculator.h"
#include "driverlib/interrupt.h"
#include "Stopwatch.h"
#include "button.h"
#include "timer.h"
#include "led.h"
#include "buzzer.h"

// Finite State Machine Counter to determine the mode
char counter=0;

// external variable from timer.c file
extern bool timer_input;


//timeout function to blink led and turn on and off buzzer



// first mode print welcome on the screen
void welcome()
{
  LCD_Print("Welcome press to","change mode");
  while(counter==0);
}


// switch case to check for the counter and call the mode function
void fsm(char c)
{
  switch (c)
  {
  case 0:
    welcome();
    return;
  case 1:
    calc();
    return;
  case 2:
    displayTime();
    return;
  case 3:
    diplay_timer();
    return;
 

  } 
}



// PortF interrupt handler which increments the counter mod the number of modes to change the mode
void PORTF_handler()
{
  while(GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_0)==1);
  if(counter==2) reset();
  if(counter==3) timer_reset();
  counter=(counter+1)%4;
  if(counter==1) LCD_Clear();
  SysCtlDelay(8000000);
  GPIOIntClear(GPIO_PORTF_BASE,GPIO_INT_PIN_0);

}

// initializes portF switch 0 as an input switch
void portF_init()
{
    // enables interrupts to the processor
    IntMasterEnable();
    
    //Run Clock Gating to enable PortF, then wait until it is ready
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF));
    
    // configure pin 0 as input pin
    GPIOUnlockPin(GPIO_PORTF_BASE, GPIO_PIN_0);
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_0);
    //GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_0,
                     //GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    
    
    // enable pin interrupts
    GPIOIntEnable(GPIO_PORTF_BASE, GPIO_INT_PIN_0); 
    GPIOIntTypeSet(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_FALLING_EDGE); 
    GPIOIntRegister(GPIO_PORTF_BASE, PORTF_handler); 
  
  
}
int main(void) {
   
  
    // init the LCD, Buttons, Keypad, LED
    SysCtlClockSet(SYSCTL_USE_OSC | SYSCTL_OSC_MAIN);
    LCD_init();
    keypad_init();
    portF_init();
    button0_init();
    button1_init();
    button2_init();
    led_init();
    buzzer_init();
    
    // make the switch which handles the modes has the highst prioritiy
    IntPrioritySet(INT_GPIOF, 0x00);
    IntPrioritySet(INT_GPIOA, 0xE0);
        
    // timer input is set only once to true    
    timer_input=true;
    while (1) {
    
      
    // call FSM function to determine the mode
    fsm(counter);

}

}
