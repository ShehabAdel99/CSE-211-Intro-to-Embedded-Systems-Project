# include "keypad.h"


// initialize the keypad ports
void keypad_init(void)
{
  
  //initialize  port C as an Output port
  
 // Enable clock gating for the port
 SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
 while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOC)){}
 
 // Configure pins as output pins
 GPIOUnlockPin(GPIO_PORTC_BASE,GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6| GPIO_PIN_7);
 GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE,GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6| GPIO_PIN_7);
  
  
 
 //initialize  port E as an Input port
 
 // Enable clock gating for the port
 SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
 while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOE)){}
 
 // Configure pins as input pins
 GPIOUnlockPin(GPIO_PORTE_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
 GPIOPinTypeGPIOInput(GPIO_PORTE_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
 GPIOPadConfigSet(GPIO_PORTE_BASE,GPIO_PIN_0,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);
 GPIOPadConfigSet(GPIO_PORTE_BASE,GPIO_PIN_1,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);
 GPIOPadConfigSet(GPIO_PORTE_BASE,GPIO_PIN_2,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);
 GPIOPadConfigSet(GPIO_PORTE_BASE,GPIO_PIN_3,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);
  
}

// read the keypad input
char  keypad_read()
{
  
   char  KEYS[4][4] = { {'1', '2', '3', '+'},
                               {'4', '5', '6', '-'},
                               {'7', '8', '9', '/'},
                               {'*', '0', '#', '='} };
  
   // Ground all output pins
   GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7,0x00000000);
 
  // If the output port is four ones, this means no key is down, return 'E' stands for error or there is no input detected
  if ((GPIOPinRead(GPIO_PORTE_BASE,GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3)&0xF) == 0xF) return 'E';
  
  // Otherwise, key was pressed, delay to debounce then re-check to make sure
  SysCtlDelay(16000);
  if ((GPIOPinRead(GPIO_PORTE_BASE,GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3)&0xF) == 0xF) return 'E';
  
  
  
  for (int i = 0; i <= 3; ++i) {
        
        // Set all output pins back HIGH (HIGH + Open-Drain = Float)
        GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7,GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);

        GPIOPinWrite(GPIO_PORTC_BASE,i==0?GPIO_PIN_4:i==1?GPIO_PIN_5:i==2?GPIO_PIN_6:i==3?GPIO_PIN_7:4,0x00000000);
        for (int j = 0; j <= 3; ++j) {
            
            // Check if any of its pins are shortcircuited to GND cause if so THAT IS THE ONE!!!!!
            if ((GPIOPinRead(GPIO_PORTE_BASE,j==0?GPIO_PIN_0:j==1?GPIO_PIN_1:j==2?GPIO_PIN_2:j==3?GPIO_PIN_3:4)&1<<j)==0) {
                
              
                // Then wait until key is released, then delay to debounce and return key
                while (!((GPIOPinRead(GPIO_PORTE_BASE,GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3)&0xF) == 0xF));
               SysCtlDelay(16000);
                return KEYS[j][i];

            }

        }

    }

    return 'E';
  
}