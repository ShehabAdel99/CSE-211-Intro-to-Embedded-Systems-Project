#include <stdbool.h>
#include <stdint.h>
#include "lcd.h"
#include <stdio.h>
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "string.h"
#include "types.h"
#include <math.h>
#include <stdlib.h>



// LCD Initializatipn function
void LCD_init() {
        
  
        // Enable clock gating for the port
        SysCtlPeripheralEnable(LCDPORTENABLE);
        
        // Configure pins as output pins
        GPIOPinTypeGPIOOutput(LCDPORT, 0xFF);

        // LCD Power ON delay always >15ms
        SysCtlDelay(50000/4); 
        
        
        //send for 4 bit initialization of LCD
        GPIOPinWrite(LCDPORT, RS,  0x00 );

        GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7,  0x30 );
        GPIOPinWrite(LCDPORT, E, 0x02);
        SysCtlDelay(10);
        GPIOPinWrite(LCDPORT, E, 0x00);

        SysCtlDelay(50000/4);

        GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7,  0x30 );
        GPIOPinWrite(LCDPORT, E, 0x02);
        SysCtlDelay(10);
        GPIOPinWrite(LCDPORT, E, 0x00);

        SysCtlDelay(50000/4);

        GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7,  0x30 );
        GPIOPinWrite(LCDPORT, E, 0x02);
        SysCtlDelay(10);
        GPIOPinWrite(LCDPORT, E, 0x00);

        SysCtlDelay(50000/4);

        GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7,  0x20 );
        GPIOPinWrite(LCDPORT, E, 0x02);
        SysCtlDelay(10);
        GPIOPinWrite(LCDPORT, E, 0x00);

        SysCtlDelay(50000/4);


        LCD_Command(0x0F); //Turn on Lcd
        LCD_Clear(); //Clear screen

}

// Takes a command to LCD
void LCD_Command(unsigned char c) {

        GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7, (c & 0xf0) );
        
        //RS=0, command reg
        GPIOPinWrite(LCDPORT, RS, 0x00);
        
        //Enable pulse
        GPIOPinWrite(LCDPORT, E, 0x02);
        
        //delay_us(1)
        SysCtlDelay(50000/4);
        
        
        GPIOPinWrite(LCDPORT, E, 0x00);

        SysCtlDelay(50000/4);
        
        //Sending lower nibble
        GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7, (c & 0x0f) << 4 );
        GPIOPinWrite(LCDPORT, RS, 0x00);
        GPIOPinWrite(LCDPORT, E, 0x02);

        SysCtlDelay(10/4);

        GPIOPinWrite(LCDPORT, E, 0x00);

        SysCtlDelay(50000/4);

}

// shows a character on the screen
void LCD_Show(unsigned char d) {
  
        //Sending upper nibble        
        GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7, (d & 0xf0) );
        //RS=1, data reg
        GPIOPinWrite(LCDPORT, RS, 0x01);
        GPIOPinWrite(LCDPORT, E, 0x02);
        
        
        
        SysCtlDelay(10*4);
        GPIOPinWrite(LCDPORT, E, 0x00);
        SysCtlDelay(50000/4);
        
        //Sending lower nibble
        GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7, (d & 0x0f) << 4 );
        GPIOPinWrite(LCDPORT, RS, 0x01);
        GPIOPinWrite(LCDPORT, E, 0x02);

        SysCtlDelay(10/4);
        GPIOPinWrite(LCDPORT, E, 0x00);
        SysCtlDelay(50000/4);

}

// moves cursor the ith row and jth column
void LCD_Cursor(char x, char y){

    if (x==0) {
        LCD_Command(0x80 + (y % 16));
        return;
    }
    LCD_Command(0xC0 + (y % 16));

}

// clears all content on the LCD
void LCD_Clear(void){

        LCD_Command(0x01);
        SysCtlDelay(10/4);

}

// prints string s on row 0 and string d on row 1
void LCD_Print(char *s, char *d) {
    int j;
    for (j=0; j<16; j++) {
        if (j<strlen(s)) {
            LCD_Cursor(0,j);
            LCD_Show(s[j]);
        }
        if (j<strlen(d)) {
            LCD_Cursor(1,j);
            LCD_Show(d[j]);
        }
    }
    LCD_Command(0xC0 + 16); //Hide cursor
}


// prints string s on the ith row
void LCD_PrintLn(char i, char *s) {
    LCD_Cursor(i, 0);
    for (i=0; i<strlen(s); i++) {
        LCD_Show(s[i]);
    }
    LCD_Command(0xC0 + 16); //Hide cursor
}

// shows a character, increments the cursor by, one hides the cursor
void LCD_show_character(unsigned char c)
{
  
  LCD_Show(c);
  LCD_Command(0x06);
  LCD_Command(0x0C);
  
}

// concatenates '-' sign to the number and print it
void LCD_PrintLn_neg(char i, char *s) {
    LCD_Cursor(i, 0);
    LCD_Show('-');
    for (i=0; i<strlen(s); i++) {
        LCD_Show(s[i]);
    }
    LCD_Command(0xC0 + 16); //Hide cursor
}

// same as LCD_PrintLn but takes the size as a parameter
void LCD_PrintLn_size(char i, char *s,char size) {
    LCD_Cursor(i, 0);
    for (i=0; i<size; i++) {
        LCD_Show(s[i]);
    }
    LCD_Command(0xC0 + 16); //Hide cursor
}

// same as LCD_PrintLn_neg but takes the size as a parameter
void LCD_PrintLn_neg_size(char i, char *s,char size) {
    LCD_Cursor(i, 0);
    LCD_Show('-');
    for (i=0; i<size; i++) {
        LCD_Show(s[i]);
    }
    LCD_Command(0xC0 + 16); //Hide cursor
}

// function to swap two numbers
void swap(uint8 *x, uint8 *y)
{
    uint8 t = *x; *x = *y; *y = t;
}
