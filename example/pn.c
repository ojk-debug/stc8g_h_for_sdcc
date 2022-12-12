#include "stc8g_sdcc.h"
#define _nop_() \
    __asm     \
        nop   \
    __endasm  
void Delay100ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	i = 2;
	j = 157;
	k = 59;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void Delay1000ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	i = 24;
	j = 27;
	k = 111;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void alert(void);
unsigned short getPreInt1(unsigned short int);
void alert2(void);

void main(void)
{
//  __data unsigned char test_data;
//  test_data = 0x1f;
    unsigned short n, temp, stack;

    P1 = 0x0;
    P1M1 = 0x0;
    P1M0 = 0x0;
    stack = n = 0;
    while(1)
    {
    Delay1000ms();
    if(n>8)
      {
      alert2();
      }
    if(stack == 1)
      {
      stack = 0;
      temp = 0x80;
      }
    else if(P1 == 0)
      {
      stack = 1;
      temp = getPreInt1(n);
      }
    else
      {
      temp = P1 >> 1;
      if(temp==0)
        {
        n++;
        }
      }
    P1 = temp;
    }
}

void alert(void)
{
  char flag;
  P1M0 = 0xff;
  P1M1 = 0;
  flag = 0;
  while(1)
  {
  flag++;
  P1=P1==0xaa?0x55:0xaa;
  if(flag>0)
    {
    P1M0=P1M0==0x00?0xff:0x0;

    flag=0;
    }
  Delay1000ms();
  }
}

void alert2()
{
  unsigned char pos, pv, pm0v, flag;
  P1M1 = 0;
  pos = 0x80;
  flag = 0; 
  while(1){
    //display
    pv = ~pos;
    pm0v = pv;
    pm0v &= ~(pos>>1);
    pm0v &= ~(pos<<1);
    P1= pv;
    P1M0 = pm0v;
    //delay
    Delay100ms();
    //prepare next
    if(flag == 0)
    {
      if(pos!=0x01)
        pos>>=1;
      else
      {
        pos<<=1;
        flag = 1;
      }
    }
    else // flag == 1
    {
      if(pos!=0x80)
        pos<<=1;
      else
      {
        pos>>=1;
        flag = 0;
      }
    }
    // end prepare
  }

  return;
}
unsigned short getPreInt1(unsigned short int n)
  {
  unsigned short int temp, temp2, i;
  temp = 0;
  for(i=1;i<=n;i++)
    {
    temp2 = 0x80;
    temp2 >>= i-1;
    temp |= temp2;
    }
  return temp;
  }

