#include<reg52.h>
#include<intrins.h>
sfr P4=0xe8;
//o¨¬¨ªa¦Ì??¡¤?¨®?¨²?¡§¨°?
sbit A0=P4^0;
sbit A1=P2^0;
sbit A2=P2^7;
//o¨¬¨ªa¡ä??D?¡Â?¨®¨º?D?o??¨²?¡§¨°?¡ê¡§?¨®¨º?¦Ì?D?o??¦Ì?a 0¡ê
sbit tube1=P4^2;
sbit tube2=P4^3;
sbit irR1=P2^1; //?¡ã
sbit irR2=P2^2; //¡Á¨®¨ªa
sbit irR3=P2^3; //¡Á¨®
sbit irR4=P2^4; //¨®¨°
sbit irR5=P2^5; //¨®¨°¨ªa
sbit Beep=P3^7;
sbit S1=P4^1;
bit irC=0 ,irL=0,irR=0,irLU=0,irRU=0;//?¡§¨°?o¨¬¨ªa¡ä??D?¡Â?¨¬2a¡Á¡ä¨¬?¨¨?????¡À?¨¢?¡ê??a 0 ?T??¡ã-
//o¨¬¨ªa¡¤¡é¨¦?????o¨º?¡§¨°?(¡ä?¨¨?¡ä??D?¡Â¡Á¨¦o?)
#define uint unsigned int
#define uchar unsigned char
	uchar code numbers[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
	void delay_ms(uint z)
{
	uchar i,j;
	while(--z)
	{
		_nop_();
		i=2;
		j=199;
		do
		{
			while(--j);
		}while(--i);
	}
}
void display(uint k)
{
	tube1=0;
	tube2=1;
	P0=numbers[k/10];
	tube1=1;
	tube2=0;
	P0=numbers[k%10];
		
}
void ir_on(uchar ch)
{
	A0=ch&0x01; 
	A1=ch&0x02; 
	A2=ch&0x04; 
}
void scan(uchar k)
{
	switch(k)
	{
		case 0:ir_on(0);
						delay_ms(5);
						if(!irR1){
							Beep=0;
							display(1);
						}
						else Beep=1;
						ir_on(5);
						delay_ms(30);
							break;
		case 1:ir_on(1);
						delay_ms(5);
						if(!irR2){
							Beep=0;
							display(2);
						}
						else Beep=1;
						ir_on(5);
						delay_ms(30);
							break;
		case 2:ir_on(2);
						delay_ms(5);
						if(!irR3){
							Beep=0;
							display(3);
						}
						else Beep=1;
						ir_on(5);
						delay_ms(30);
							break;
		case 3:ir_on(3);
						delay_ms(5);
						if(!irR4){
							Beep=0;
							display(4);
						}
						else Beep=1;
						ir_on(5);
						delay_ms(30);
							break;
		case 4:ir_on(4);
						delay_ms(5);
						if(!irR5){
							Beep=0;
							display(5);
						}
						else Beep=1;
						ir_on(5);
						delay_ms(30);
							break;
		default:break;
		}
}
void main()
{
	uchar k=0;
	while(1)
	{
		scan(k);
		if(!S1)
		{
			delay_ms(10);
			if(!S1)
			{
				k++;
			}
			while(!S1);
			delay_ms(10);
			while(!S1);
			if(k==5)
				k=0;
			}
		}
		
}
