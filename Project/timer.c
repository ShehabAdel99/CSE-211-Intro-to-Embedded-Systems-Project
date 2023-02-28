#include "timer.h"
#include "led.h"
#include <stdio.h>
#include "buzzer.h"
// initialze the keypad input variable
uint8 keypad_input;

extern char counter;

// flag to know if the user is entering the timer input or nor
bool timer_input=false;

// initialize the timer clock variables
int16 seconds_right_t=0 ,seconds_left_t=0 , minutes_right_t=0, minutes_left_t=0;



//timeout function to blink led and turn on and off buzzer
void timeout()
{
   GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_5|GPIO_PIN_6,GPIO_PIN_5|GPIO_PIN_6);
   SysCtlDelay(8000000);
   GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_5|GPIO_PIN_6,000000);
   SysCtlDelay(8000000);
   GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_5|GPIO_PIN_6,GPIO_PIN_5|GPIO_PIN_6);
   SysCtlDelay(8000000);
   GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_5|GPIO_PIN_6,000000);
   SysCtlDelay(8000000);
   GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_5|GPIO_PIN_6,GPIO_PIN_5|GPIO_PIN_6);
   SysCtlDelay(8000000);
   GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_5|GPIO_PIN_6,000000);

   
  
}



// initialize timer and start counting down
void timer_start()
{
    // 1. Run Clock Gating to enable GPTM Timer0, then wait until it is ready
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER0));
    
    // 2. Disable Timer0
    TimerDisable(TIMER0_BASE, TIMER_A);
    
     // 3. Configure Timer0 to be in periodic count-down concatenated mode
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
    TimerControlStall(TIMER0_BASE, TIMER_A, true);
    
    // 4. Set Timer0 Interval Load to 1s
    TimerLoadSet(TIMER0_BASE, TIMER_A, (16000000-1));
    
    // 5. Clear Interrupt Flag just in case it was up from any previous code
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    
    // 6. Enable Timer0
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    TimerEnable(TIMER0_BASE, TIMER_A);
    TimerIntRegister(TIMER0_BASE, TIMER_A,timer0A_ISR);
  
}


// timer 0A Interrupt handler which handles the cases of the clock variables
void timer0A_ISR()
{
  
  TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
  seconds_right_t--;
  if(minutes_left_t==0&&minutes_right_t==0&&seconds_left_t==0&&seconds_right_t==-1)
  {
    //trigger buzzer
    TimerDisable(TIMER0_BASE, TIMER_A);
    TimerIntDisable(TIMER0_BASE, TIMER_A);
      timeout();
     minutes_left_t=0;
     minutes_right_t=0;
     seconds_left_t=0;
     seconds_right_t=0;
     timer_input=true;
    
  }
  if(seconds_left_t==0&&seconds_right_t==-1)
  {
   
    minutes_right_t--;
    seconds_right_t=9;
    seconds_left_t=5;
  }
  
  if(minutes_right_t==-1)
  {
    
    minutes_left_t--;
    minutes_right_t=9;
    seconds_right_t=9;
    seconds_left_t=5;
    
  }
  
  if(seconds_right_t==-1)
  {
    seconds_right_t=9;
    seconds_left_t--;
  }
  
  
  
  
}

// display timer clock variables on the screen
void diplay_timer()
{
  // if the input flag is true take time from the user
  if(timer_input)
  {
    LCD_Clear();
    SysCtlDelay(4000000);
    LCD_Print("00:00","Timer");
    SysCtlDelay(4000000);
       
    
      // wait until user enters a number from keypad and store it the minutes left variable
       
      LCD_Cursor(0,0);
      LCD_Command(0x0E);
       while(1)
       {
         if(counter!=3) return;
         keypad_input=keypad_read();
         if (keypad_input!='E') break;
       }
       LCD_Show(keypad_input);
       minutes_left_t=(uint8)keypad_input-'0';
       
       
       // wait until user enters a number from keypad and store it the minutes right variable
       LCD_Cursor(0,1);
       LCD_Command(0x0E);
       while(1)
       {
         if(counter!=3) return;
         keypad_input=keypad_read();
         if (keypad_input!='E') break;
       }
       LCD_Show(keypad_input);
       minutes_right_t=(uint8)keypad_input-'0';
       
       
       // wait until user enters a number from keypad and store it the seconds left variable
       LCD_Cursor(0,3);
       LCD_Command(0x0E);
       while(1)
       {
         if(counter!=3) return;
         keypad_input=keypad_read();
         if (keypad_input!='E') break;
       }
       LCD_Show(keypad_input);
       seconds_left_t=(uint8)keypad_input-'0';
       
       
       // wait until user enters a number from keypad and store it the seconds right variable
       LCD_Cursor(0,4);
       LCD_Command(0x0E);
       while(1)
       {
         if(counter!=3) return;
         keypad_input=keypad_read();
         if (keypad_input!='E') break;
       }
       LCD_Show(keypad_input);
       seconds_right_t=(uint8)keypad_input-'0';
    
       
    // hide the cursor and make the input flag false   
    LCD_Command(0x0C);  
    timer_input=false;
    
    // wait until user enters D from the keypad to start the timer
    while(keypad_input!='=')
    {
      if(counter!=3) return;
      keypad_input=keypad_read();
    }
      timer_start();
  }
  
  
  
  // show time variables on the LCD
  //char timer[6];
  LCD_Cursor(0,0);
  LCD_Show((char)(minutes_left_t+'0'));
  LCD_Command(0x0C);
  
  LCD_Cursor(0,1);
  LCD_Show((char)(minutes_right_t+'0'));
  LCD_Command(0x0C);
  
  LCD_Cursor(0,2);
   LCD_Show(':');
    
  LCD_Cursor(0,3);
  LCD_Show((char)(seconds_left_t+'0'));
  LCD_Command(0x0C);
  
   LCD_Cursor(0,4);
  LCD_Show((char)(seconds_right_t+'0'));
  LCD_Command(0x0C);

 
 
  
}
void timer_reset(){
     minutes_left_t=0;
     minutes_right_t=0;
     seconds_left_t=0;
     seconds_right_t=0;
     timer_input=true;
     //TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
     //TimerDisable(TIMER0_BASE, TIMER_A);
     //TimerIntDisable(TIMER0_BASE, TIMER_A);
     
     
  
  
  
  
}