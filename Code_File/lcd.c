#include<LPC21XX.H>
#include "delay.c"

#define LCD_D 0xff  // P0.00 - P0.7
#define RS 1<<10          // P0.10
#define E 1<<11           // P0.11

void LCD_INIT(void);
void LCD_CMD(unsigned char);
void LCD_DATA(unsigned char);
void LCD_STR(unsigned char*);


void LCD_INIT(void){
	
	IODIR0|=LCD_D|RS|E;
	LCD_CMD(0x01);
	LCD_CMD(0x02);
	LCD_CMD(0x0C);
	LCD_CMD(0x38);
}

void LCD_CMD(unsigned char cmd){
	
	IOCLR0=LCD_D;
	IOSET0=cmd;
	IOCLR0=RS;
	IOSET0=E;
	delay_ms(2);
	IOCLR0=E;
}

void LCD_DATA(unsigned char d){
	
	IOCLR0=LCD_D;
	IOSET0=d;
	IOSET0=RS;
	IOSET0=E;
	delay_ms(2);
	IOCLR0=E;
}

void LCD_STR(unsigned char *s)
{
	while(*s)
		LCD_DATA(*s++);
	
}
