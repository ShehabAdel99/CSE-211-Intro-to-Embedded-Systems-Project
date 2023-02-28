#include <stdbool.h>
#include <stdint.h>
#include "lcd.h"
#include "keypad.h"
#include "driverlib/sysctl.h"
#include <stdio.h>
#include "queue.h"
#include "types.h"
#include <string.h>

// modes counter
extern char counter;

void calc(void)
{
  // create queue object
  QueuePtr queue = create_empty_queue();

        
        uint8 key = 0;

        // Keep trying to read until you receive an '='
        while (key != '=') {
          
            // break if the mode isn't calculator
            if(counter !=1) return; 
            key = keypad_read();
            
            // if the user pressed # clear the queue and start getting input from the first
            if(key=='#'){
              LCD_Clear();
              clear_queue(queue);
              return;
            }
            
            // if it's a valid key show it on LCD and enqueue into the queue
            if (key != 'E') {

                LCD_show_character(key);
                enqueue(queue, key);

            }

        }

        // ACTUAL ARITHMETIC LOGIC

        int32 operand1 = 0;
        uint8 operator = '0';
        int32 operand2 = 0;
        
        
        // get the first operand from the queue
        while (!(is_empty(queue))) {

            key = front(queue);
            if (!(key >= '0' && key <= '9')) break;

            operand1 *= 10;
            operand1 += (int32) (key - '0');
            dequeue(queue);

        }
        //  get the opearor
        operator = front(queue);
        dequeue(queue);
        
        
        // get the second operand from the queue
        while (!(is_empty(queue))) {

            key = front(queue);
            if (!(key >= '0' && key <= '9')) break;

            operand2 *= 10;
            operand2 += (int32) (key - '0');
            dequeue(queue);

        }

        int32 result = 0;
        
        
        
        // perform the operation
        switch (operator) {

            case '+':
                result = operand1 + operand2;
                break;

            case '-':
                result = operand1 - operand2;
                break;

            case '/':
                if (operand2) result = operand1 / operand2;
                break;

            case '*':
                result = operand1 * operand2;
                break;

        }

        
        int z=0;  // number of digits of the answer
        bool neg=false; // flag to know if the result is negative or not
        
        
        
        if(result!=0){
          
          // if the result is negative multiply it by -1 and set the negative flag true
          if(result<0){
          result*=-1;
          neg=true;
        }
        
        // get the number of digits in the result
        int32 res2=result;
        while(result)
        {
          result/=10;
          z++;
        } 
        
        // create a dynamic allocated array of a sttring of digits
        char * res = malloc(z*sizeof(char));
        for(int i=z-1;i>=0;i--)
        {
          res[i]=(res2%10)+'0';
          res2/=10;
        }
        
        for(int k=0;k<strlen(res);k++) printf("%c",res[k]);
        
        
        // if the result is negative show a negative sign on the screen and show the answer
        if(neg){
          LCD_PrintLn_neg_size(1,res,z);
          
        }
        
        // if the result is positive show only the result without negative sign
        else LCD_PrintLn_size(1,res,z);
        
        }
        
        // if the result is zerp show zero
        else LCD_PrintLn(1,"0");
        clear_queue(queue);
           
    
    }

  
  
  
  