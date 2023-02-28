#include "Stopwatch.h"
#include "types.h"
#include "lcd.h"

// define the clock variables and initialize by zero
uint8 seconds_right=0 ,seconds_left=0 , minutes_right=0, minutes_left=0;


// SysTick Interrupt Handler
void SysTickHandler()
{
  seconds_right++;
  if(seconds_right==10&&seconds_left==5&&minutes_right==9)
  {
    seconds_right=0;
    seconds_left=0;
    minutes_right=0;
    minutes_left++;
  }
  else if(seconds_right==10&&seconds_left==5)
  {
    seconds_left=0;
    seconds_right=0;
    minutes_left=0;
    minutes_right++;
  }
  
  else if (seconds_right==10)
  {
    
    seconds_right=0;
    seconds_left++;
  }
  else if(seconds_right==10&&seconds_left==5&&minutes_right==9)
  {
    seconds_right=0;
    seconds_left=0;
    minutes_right=0;
    minutes_left++;
  }
  

  
}



// displays the time variables on the LCD
void displayTime(void)
{
  
  LCD_Cursor(0,0);
  LCD_Show((char)(minutes_left+'0'));
  LCD_Command(0x0C);
  
  LCD_Cursor(0,1);
  LCD_Show((char)(minutes_right+'0'));
  LCD_Command(0x0C);
  
  LCD_Cursor(0,2);
   LCD_Show(':');
    
  LCD_Cursor(0,3);
  LCD_Show((char)(seconds_left+'0'));
  LCD_Command(0x0C);
  
    LCD_Cursor(0,4);
  LCD_Show((char)(seconds_right+'0'));
  LCD_Command(0x0C);
  
  
	
}

// start the stopwatch
void start(void)
{
  SysTickDisable(); // 1. Disable timer
    SysTickIntDisable(); // 2. Disable timer interrupt
    SysTickPeriodSet(16000000-1); // 3. Set required period
    SysTickIntRegister(SysTickHandler); // 4. Register ISR
    SysTickIntEnable(); // 5. Enable timer interrupt
    SysTickEnable(); // 6. Enable timer
    GPIOIntClear(GPIO_PORTA_BASE,GPIO_INT_PIN_2);


}

// stop the stopwatch and reset the variables
void reset(void)
{
  
  SysTickDisable(); // 1. Disable timer
  SysTickIntDisable(); // 2. Disable timer interrupt
   seconds_right=0;
   seconds_left=0;
   minutes_right=0;
   minutes_left=0;
   GPIOIntClear(GPIO_PORTA_BASE,GPIO_INT_PIN_4);
}

// stop the stopwatch
void pause(void)
{
 SysTickDisable(); // 1. Disable timer
 SysTickIntDisable(); // 2. Disable timer interrupt 
 GPIOIntClear(GPIO_PORTA_BASE,GPIO_INT_PIN_3);
  
}


// a funnction to check from which  pin the interrupt was raised
void PORTA_handler(void)
{
  
  // if it was raised from pin 2 call the function start
  if(GPIOIntStatus(GPIO_PORTA_BASE,true)==1<<2)
  {
    start();
  }
  
  // if it was raised from pin 3 call the function pause
  else if (GPIOIntStatus(GPIO_PORTA_BASE,true)==1<<3)
  {
    
    pause();
  }
  
  // if it was raised from pin 4 call the function reset
  else if (GPIOIntStatus(GPIO_PORTA_BASE,true)==1<<4)
  {
    reset();
  }
  
  
}

