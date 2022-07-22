#include<reg52.h>
unsigned char code forward[8]={0x11,0x93,0x82,0xc6,0x44,0x6c,0x28,0x39};
unsigned char code right[8]={0x11,0x33,0x22,0x66,0x44,0xcc,0x88,0x99};
unsigned char code left[8]={0x11,0x99,0x88,0xcc,0x44,0x66,0x22,0x33};
unsigned char flag = 0;
unsigned char top = 0;
unsigned char num = 0;
unsigned char n=0,m=0;
unsigned char maze[8][8];
unsigned char stockx[20];
unsigned char stocky[20];
unsigned char is1=0,is2=0,is3=1,is4=1,is5=0;//0???,1???
unsigned char  list[8][8];
unsigned char derection = 0;
unsigned char next;   
sfr P4=0xe8;
sbit A0 = P4^0;
sbit A1 = P2^0;
sbit A2 = P2^7;
sbit irR1 = P2^1;
sbit irR2 = P2^2;//×óÇ°
sbit irR3 = P2^3;
sbit irR4 = P2^4;
sbit irR5 = P2^5;//ÓÒÇ°

void init()
{
	unsigned char i,j;
	stockx[0] = 0;
	stocky[0] = 0;
	
	for(i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
		{
			maze[i][j] = 0xff;
			list[i][j] = 79;
		}
	}
	maze[0][0]=0xf7;
	list[0][0]=0;
}
void delay(unsigned int x)
{
	unsigned int i,j;
	for(i=0;i<x;i++)
	{
		for(j=0;j<114;j++);
	}
}

void irON (unsigned char x)
{
	A0 = x&(0x01);
	A1 = x&(0x02);
	A2 = x&(0x04);
}


void ir1()//?
{
	if(irR1==0)//??
	{
		is1=1;
		//P0 = table[1];
	}
	else
	{
		is1=0;
		num++;
		//P0=table[0];
	}
}
void ir2()//??
{
	if(irR2==0)
		is2=1;
	else
	{
		is2=0;
	}
}
void ir3()//?
{
	if(irR3==0)
		is3=1;
	else
	{
		is3=0;
		num++;
	}
}
void ir4()//?
{
	if(irR4==0)
		is4=1;
	else
	{
		is4=0;
		num++;
	}
}
void ir5()//??
{
	if(irR5==0)
		is5=1;
	else
	{
		is5=0;
	}
}
void deternm(unsigned char s)
{
	if(s==0)
		m++;
	if(s==1)
		n++;
	if(s==2)
		m--;
	if(s==3)
		n--;
}
void deternext(unsigned char s)
{
	if(s==0)
		next = 0x8f;
	else if(s==1)
		next = 0x4f;
	else if(s==2)
		next = 0x2f;
	else if(s==3)
		next = 0x1f;
}
unsigned char deterwallmessage()
{
	unsigned char t;
	if(derection == 0)
	{
		t = is1*8+is4*4+is3;
	}
	else if(derection ==1)
	{
		t = is1*4+is3*8+is4*2;
	}
	else if(derection == 2)
	{
		t = is1*2+is4+is3*4;
	}
	else if(derection == 3)
	{
		t = is1+is4*8+is3*2;
	}
	return t;
	
}
 char  forwmazex(unsigned char x)
{
	if(x==0)
		return 0;
	else if(x==1)
		return 1;
	else if(x==2)
		return 0;
	else if(x==3)
		return -1;
	return 0;
}
 char forwmazey(unsigned char x)
{
		if(x==0)
		return 1;
	else if(x==1)
		return 0;
	else if(x==2)
		return -1;
	else if(x==3)
		return 0;
	return 0;
}
void debugcar()
{
	unsigned char x,y;
	if(is5==1)
	{
		for(y=0;y<5;y++)
	{
		for(x=0;x<8;x++)
		{
			P1 = left[x]&0xf0;
			delay(2);
		}
	}
  }
	else if(is2==1)
	{
		for(y=0;y<5;y++)
	{
		for(x=0;x<8;x++)
		{
			P1 = right[x]&0x0f;
			delay(2);
		}
	}
  }
}
 char  rigmazex(unsigned char x)
{
	if(x==0)
		return 1;
	else if(x==1)
		return 0;
	else if(x==2)
		return -1;
	else if(x==3)
		return 0;
	return 0;
}
 char rigmazey(unsigned char x)
{
		if(x==0)
		return 0;
	else if(x==1)
		return -1;
	else if(x==2)
		return 0;
	else if(x==3)
		return 1;
	return 0;
}
 char  lefmazex(unsigned char x)
{
	if(x==0)
		return -1;
	else if(x==1)
		return 0;
	else if(x==2)
		return 1;
	else if(x==3)
		return 0;
	return 0;
}
 char lefmazey(unsigned char x)
{
		if(x==0)
		return 0;
	else if(x==1)
		return 1;
	else if(x==2)
		return 0;
	else if(x==3)
		return -1;
	return 0;
}
void forw()
{
	unsigned char i,j;
	for(j=0;j<108;j++)
	{
		
		for(i=0;i<8;i++)
		{
			P1 = forward[i];
			delay(2);
		}
		if((j+1)%25==0)
		{
					is2=0;
					is5=0;
			    irON(1);
					delay(5);
					ir2();
				  irON(5);
			    irON(4);
					delay(5);
					ir5();
				  irON(5);
					debugcar();
		}
	}
	
}

void lef()
{
	unsigned char i,j;
	for(j=0;j<51;j++)
	{
		for(i=0;i<8;i++)
		{
			P1 = left[i];
			delay(2);
		}
	}
	derection = (derection+3)%4;
}
void rig()
{
	unsigned char i,j;
	for(j=0;j<51;j++)
	{
		for(i=0;i<8;i++)
		{
			P1 = right[i];
			delay(2);
		}
	}
	derection = (derection+1)%4;
}

void creatlist()
{
	unsigned char i,head = 0,tail = 1,sum = 0;
	for(i=0;i<20;i++)
	{
		stockx[i] = 0;
		stocky[i] = 0;
	}
	stockx[head] = 0;
	stocky[head] = 0;
	while(1)
	{
		if((head==tail))
			break;
		  n=stockx[head%20];
			m=stocky[head%20];
		if((maze[n][m]&0x08)!=0x08)
		{
			
			sum++;
			if(sum<list[n][m+1])
			{
				list[n][m+1] = sum;
				stockx[tail%20]=n;
				stocky[tail%20]=m+1;
			  tail++;
			}
			sum--;
		}
		if((maze[n][m]&0x04)!=0x04)
		{
		
			sum++;
			if(sum<list[n+1][m])
			{
				list[n+1][m] = sum;
				stockx[tail%20]=n+1;
				stocky[tail%20]=m;
			  tail++;
			}
			sum--;
		}
		if((maze[n][m]&0x02)!=0x02)
		{

			sum++;
			if(sum<list[n][m-1])
			{
				list[n][m-1] = sum;
				stockx[tail%20]=n;
				stocky[tail%20]=m-1;
			  tail++;
			}
			sum--;
		}
		if((maze[n][m]&0x01)!=0x01)
		{
			
			sum++;
			if(sum<list[n-1][m])
			{
				list[n-1][m] = sum;
				stockx[tail%20]=n-1;
				stocky[tail%20]=m;
			  tail++;
			}
			sum--;
		}
		head++;
		n=stockx[head%20];
		m=stocky[head%20];
		if(sum!=list[n][m])
			sum++;
	}
	sum = list[7][7];
	n=7;
	m=7;
	for(i=0;i<20;i++)
	{
		stockx[i] = 0;
		stocky[i] = 0;
	}
	i=0;
	stockx[i]=7;
	stocky[i]=7;
	while(sum!=0)
	{
		if((n-1>=0)&&(n-1<=7)&&(list[n-1][m] == (sum-1))&&((maze[n][m]&0x01)!=0x01))
		{
			i++;
			stockx[i]=n-1;
	    stocky[i]=m;
			n--;
			sum--;
		}
		else if((n+1>=0)&&(n+1<=7)&&(list[n+1][m] == (sum-1)) &&((maze[n][m]&0x04)!=0x04))
		{
			i++;
			stockx[i]=n+1;
	    stocky[i]=m;
			n++;
			sum--;
		}
		else if((m-1>=0)&&(m-1<=7)&&(list[n][m-1] == (sum-1)) &&((maze[n][m]&0x02)!=0x02))
		{
			i++;
			stockx[i]=n;
	    stocky[i]=m-1;
			m--;
			sum--;
		}
		else if((m+1>=0)&&(m+1<=7)&&(list[n][m+1] == (sum-1)) &&((maze[n][m]&0x08)!=0x08))
		{
			i++;
			stockx[i]=n;
	    stocky[i]=m+1;
			m++;
			sum--;
		}
	}
	n=0;
	m=0;
	while((n!=7)||(m!=7))
	{
		if(stocky[i-1]-stocky[i]==1)
		{
			if(derection == 1)
			{
				lef();
				forw();
				m++;
			}
			else
			{
				forw();
			m++;
			}
		}
		else 
		{
			if(derection==1)
			{
				forw();
				n++;
			}
			else
			{
			rig();
			forw();
			n++;
			}
		}
		i--;
	}
	while(1);
}
	
void reverse()
{
	if((maze[n][m]|0x0f)==0x8f)
	{
		if(derection == 0)
		{
			rig();
			rig();
			forw();
			deternm(derection);
			
		}
		else if(derection == 1)
		{
			rig();
			forw();
			deternm(derection);
			
		}
		else if(derection == 2)
		{
			forw();
			deternm(derection);
			
		}
		else if(derection == 3)
		{
			lef();
			forw();
			deternm(derection);
			
		}
	}
	
	else if((maze[n][m]|0x0f)==0x4f)
	{
		if(derection == 0)
		{
			lef();
			forw();
			deternm(derection);
			
		}
		
		else if(derection == 1)
		{
			rig();
			rig();
			forw();
			deternm(derection);
			
		}
		else if(derection == 2)
		{
			rig();
			forw();
			deternm(derection);
			
		}
		else if(derection == 3)
		{
			forw();
			deternm(derection);
			
		}
	}
	
	else if((maze[n][m]|0x0f)==0x2f)
	{
		if(derection == 0)
		{
			forw();
			deternm(derection);
			
		}
		
		else if(derection == 1)
		{
			lef();
			forw();
			deternm(derection);
			
		}
		else if(derection == 2)
		{
			rig();
			rig();
			forw();
			deternm(derection);
			
		}
		else if(derection == 3)
		{
			rig();
			forw();
			deternm(derection);
			
		}
	}
	
	else if((maze[n][m]|0x0f)==0x1f)
	{
		if(derection == 0)
		{
			rig();
			forw();
			deternm(derection);
			
		}
		
		else if(derection == 1)
		{
			forw();
			deternm(derection);
			
		}
		else if(derection == 2)
		{
			lef();
			forw();
			deternm(derection);
			
		}
		else if(derection == 3)
		{
			rig();
			rig();
			forw();
			deternm(derection);
			
		}
	}

}


void oper()//???,???????????????,???????nm????,??????????
{ 
	
	if((n==stockx[top])&&(m==stocky[top])&&(n!=0||m!=0))
	{
		if((is4==0)&&(maze[n+rigmazex(derection)][m+rigmazey(derection)]==0xff))//?
	{
		rig();
		forw();
		deternext(derection);
		deternm(derection);
		maze[n][m]=(maze[n][m]&next);
		
	}
	else if((is1==0)&&(maze[n+forwmazex(derection)][m+forwmazey(derection)]==0xff))//?
	{
		forw();
		deternext(derection);
		deternm(derection);
		maze[n][m]=(maze[n][m]&next);
		
	}
	else if((is3==0)&&(maze[n+lefmazex(derection)][m+lefmazey(derection)]==0xff))//?
	{
		lef();
		forw();
		deternext(derection);
		deternm(derection);
		maze[n][m]=(maze[n][m]&next);
		
		
	}
	else 
	{
		top--;
		while(1)
		{
			if((n==stockx[top])&&(m==stocky[top]))
				break;
			reverse();
		}
		if(top == 0)
		{
			  rig();
				rig();
				creatlist();
		}
		
  }
  }
	else 
	{
		if((is4==0)&&(maze[n+rigmazex(derection)][m+rigmazey(derection)]==0xff))//?
	{
		rig();
		forw();
		deternext(derection);
		deternm(derection);
		maze[n][m]=(maze[n][m]&next);
		
	}
	else if((is1==0)&&(maze[n+forwmazex(derection)][m+forwmazey(derection)]==0xff))//?
	{
		forw();
		deternext(derection);
		deternm(derection);
		maze[n][m]=(maze[n][m]&next);
	
	}
	else if((is3==0)&&(maze[n+lefmazex(derection)][m+lefmazey(derection)]==0xff)) //?
	{
		lef();
		forw();
		deternext(derection);
		deternm(derection);
		maze[n][m]=(maze[n][m]&next);
	}
	else
	{
		while(1)	
		{
			if((n==stockx[top])&&(m==stocky[top]))
				break;
			reverse();
		}
	}
}
}
void test()
{
	unsigned char wallmessage;
	
	
	while(flag!=3)
	{
	switch(flag)
			{
				case 0:
					irON(0);
					delay(10);
					ir1();
				  irON(5);
					break;
				case 1:
					irON(2);
					delay(10);
					ir3();
				  irON(5);
					break;
				case 2:
					irON(3);
					delay(10);
					ir4();
				  irON(5);
					break;
	
			}
			flag++;
			delay(10);
		}
	flag=0;
		if(num>1&&(n!=stockx[top]||m!=stocky[top]))
		{
			top++;
			stockx[top] = n;
			stocky[top] = m;
			
		}
		num = 0;
		wallmessage = deterwallmessage(); 
		if((maze[n][m]|0xf0)==0xff)
		maze[n][m]=(maze[n][m]&(wallmessage+240));
	
}

void main()
{
	init();
	delay(500);
	while(1)
	{
		oper();
		test();
	}
}
