#ifndef LCD_H_
#define LCD_H_
// Define common used macros in LCD
#define LCDPORT         GPIO_PORTB_BASE
#define LCDPORTENABLE   SYSCTL_PERIPH_GPIOB
#define RS              GPIO_PIN_0
#define E               GPIO_PIN_1
#define D4              GPIO_PIN_4
#define D5              GPIO_PIN_5
#define D6              GPIO_PIN_6
#define D7              GPIO_PIN_7
#include "types.h"


void LCD_init(void);                                //LCD initialization
void LCD_Command(unsigned char c);                  //Send command
void LCD_Show(unsigned char d);                     //Show a char

void LCD_Clear(void);                               //Clear the screen
void LCD_Print(char *s, char *d);                   //Print 2 lines
void LCD_PrintLn(char i, char *s);                  //Print specific line
void LCD_PrintJustify(char i, char *s, char *d);    //Print specific line floated left and floated right text
void LCD_Cursor(char x, char y);                    //Set cursor
void LCD_show_character(unsigned char c);           // show one character on the LCD and move the cursor one digit to the right and hide the cursor
void LCD_PrintLn_neg(char i, char *s);
void LCD_PrintLn_size(char i, char *s,char size);
void LCD_PrintLn_neg_size(char i, char *s,char size);
#endif /* LCD_H_ */