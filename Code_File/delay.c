#include<LPC21XX.H>

typedef unsigned int U32;

void delay_s(U32 s)
{
	T0PR=15000000-1;
	T0TCR=0x01;
	while(T0TC<s);
	T0TCR=0x03;
	T0TCR=0x00;
}

void delay_ms(U32 ms)
{
	T0PR=15000-1;
	T0TCR=0x01;
	while(T0TC<ms);
	T0TCR=0x03;
	T0TCR=0x00;
}

void delay_mis(U32 mis)
{
	T0PR=15-1;
	T0TCR=0x01;
	while(T0TC<mis);
	T0TCR=0x03;
	T0TCR=0x00;
}
