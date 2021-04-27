/*
 * TEST.cpp
 *
 * Created: 08.04.2021 20:06:10
 * Author : SKB.MAKEY.SAVVA.KOSMACHEV.
 */ 

#define F_CPU 10000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#define Button PORTB
#define LED PORTD
#define Transistor PORTC
unsigned int R1=0,R2=0,R3=0,R4=0;
char t=1;
int time1=0;
int C=0, i=0;
int R=0;
int S=0;
unsigned int n=0;
char flag_Button1=0,flag_Button2=0,flag_Dopusk=0;
uint8_t F_n1 = 0;
unsigned int number[10]=
{
	0b00111111,
	0b00000110,
	0b01011011,
	0b01001111,
	0b01100110,
	0b01101101,
	0b01111101,
	0b00000111,
	0b01111111,
	0b01101111
};
unsigned int numbar[10]=
{
	0b10111111,
	0b10000110,
	0b11011011,
	0b11001111,
	0b11100110,
	0b11101101,
	0b11111101,
	0b10000111,
	0b11111111,
	0b11101111
};
void Num(unsigned int N)
{
	R1=numbar[N/1000];
	R2=number[N%1000/100];
	R3=number[N%100/10];
	R4=number[N%10];
}
ISR(TIMER0_OVF_vect)
{
	LED=0b01100000;
	if(t==1)
	{
		Transistor=0b00000001;
		LED=R1;
	}
	if(t==2)
	{
		Transistor=0b00000010;
		LED=R2;
	}
	if(t==3)
	{
		Transistor=0b00000100;
		LED=R3;
	}
	if(t==4)
	{
		Transistor=0b00001000;
		LED=R4;
	}
	t++;
	if(t==5)
	{
		t=1;
	}
	
}
void Stop(void)
{
	R1=0b01110001;
	R2=0b00111110;
	R3=0b00111000;
	R4=0b00111000;
	
}


int main(void)
{   uint8_t	Flag_LGBT = 0;
	DDRD=0b11111111;
	DDRC=0b00011111;
	DDRB=0b0;
	PORTB=0b00001111;
	LED =number[0];
	TCCR0|=(1<<1);
	TCCR0&=~(1<<0);
	TCCR0&=~(1<<2);
	TIMSK|=(1<<0);
	sei();
	
	
	TCCR1B=0b0;
	
	TCNT1H=0;
	TCNT1L=0;
    while (1) 
    {
		TCNT1H=0;
		//Start
		if((PINB&(1<<0))&&(flag_Button1==0 && Flag_LGBT == 0))
		{
			TCNT1L=0;
			TCCR1B=0b0000010;
			flag_Button1=1;
			R=1;
		}
		if((~PINB&(1<<0))&&(flag_Button1==1))
		{
			flag_Button1=0;
			Flag_LGBT = 1;
		}
		switch(R)
		{
			case 1:
			if(TCNT1H<=255 && TCNT1L==0)
			{
				Num(C);
				C++;
				
			}
			break;
			case 0:
			Num(C);
			break;
			case 3:
			Stop();
			break;
		}
		//Stop
		if((~PINB&(1<<1))&&(flag_Button2==0))
		{
			flag_Button2=1;
			R=0;
		}
		if((PINB&(1<<1))&&(flag_Button2==1))
		{
			flag_Button2=0;
		}
		if(C>9999) R=3;
    }
}

