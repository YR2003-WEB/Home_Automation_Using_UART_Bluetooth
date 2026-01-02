#include <LPC21xx.h>
#include "lcd.c"

/* LED Pin */
#define LED        (1 << 15)      // P0.16


/* UART0 Initialization */
void uart0_init(void)
{
    PINSEL0 |= 0x50000;   // P0.0 TXD0, P0.1 RXD0
    U1LCR = 0x83;            // 8-bit, DLAB=1
    U1DLL = 97;              // 9600 baud @ 15MHz
    U1DLM = 0;
    U1LCR = 0x03;            // DLAB=0
}

/* UART Receive */
char uart0_rx(void)
{
    while(!(U1LSR & 0x01));
    return U1RBR;
}
// to check on virtual terminal
void uart0_tx(unsigned char tx)
{
	U1THR=tx;
    while(!((U1LSR>>5) & 0x01));
}

/* MAIN PROGRAM */
int main(void)
{
    char rx;
	

    IODIR0 |= LED;           // LED as output
    IOSET0 = LED;            // LED OFF

    uart0_init();
    LCD_INIT();
		LCD_CMD(0X01); 
	  LCD_CMD(0X80);
	  LCD_STR("Bluetooth Home");
    LCD_CMD(0xC0);
    LCD_STR("Automation");

    while(1)
    {
        rx = uart0_rx(); 
		    uart0_tx(rx);    // Receive data from Bluetooth
		    delay_ms(10);

        if(rx == 'A')
        {
            IOCLR0 = LED;    // LED ON
            LCD_CMD(0x01);
            LCD_STR("LED STATUS:");
            LCD_CMD(0xC0);
            LCD_STR("LED ON");
        }
        else if(rx == 'a')
        {
            IOSET0 = LED;    // LED OFF
            LCD_CMD(0x01);
            LCD_STR("LED STATUS:");
            LCD_CMD(0xC0);
            LCD_STR("LED OFF");
        }
    }
}
