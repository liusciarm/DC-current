#include<reg52.h>

#define uchar unsigned char
#define uint  unsigned int
sbit key1=P1^0;                                      //端口定义,选择光标在个位或十位 
sbit key2=P1^1;                                     //光标处电压为1输出 
sbit rs=P1^4;
sbit en=P1^5;
sbit DAC_CS=P3^2;
sbit DAC_WR=P3^6;
sbit ADC_CS=P0^0;
sbit ADC_DI=P0^1;
sbit ADC_DO=P0^2;
uchar code table1[]="  liu do";                 //初始化显示
uchar code table2[]="  dianya :0.0V ";                //初始化电源
uchar volt=0;

void delay(uint z)                                     
       
{
  uint x,y;
   for(x=z;x>0;x--)
    for(y=110;y>0;y--);
}

void write_com(uchar com)                             
{
   rs=0;                                             
   en=0;
   P0=com;
   delay(5);
   en=1;                                           
   delay(5);
   en=0;
}

void write_date(uchar date)                         
{
   rs=1;                                        
   en=0;
   P0=date;
   delay(5);
   en=1;                                              
   delay(5);
   en=0;
}

void write_sfm(uchar add,uchar date)
{
	uchar qian,bai,shi,ge;
        uint temp = (date/128.0)*1000;
	qian=temp/1000;
	bai =temp%1000/100;
	shi =temp%100/10;
	ge  =temp%10;
	write_com(0x80+0x40+add);
	write_date(0x30+qian);
	write_date(0x30+bai);
	write_date('.');//???
	write_date(0x30+shi);
	write_date(0x30+ge); 
	write_date('V');//??
}
void Init()                                      
{  
    uchar num;
    en=0;
    write_com(0x38);                          //置地址
	write_com(0x0c);                            
	write_com(0x06);                          //光标右移
	write_com(0x01);                          //清显示
	write_com(0x80);                          //lcd DDRAM设置
     for(num=0;num<16;num++)
		{
			write_date(table1[num]);
			delay(50);
		}
	write_com(0x80+0x40);                    //lcd第二行                 
	for(num=0;num<14;num++)
		{
			write_date(table2[num]);
			delay(50);
		}
}

void write_voltage(uchar add,uchar dat)            
   { 
     write_com(0x80+0x40+add);                      //确定第二行位置
     write_date(0x30+dat);                          //写数据
   }

void DA0832out(uchar dadata)                       
{
  
   DAC_CS=0;
   P0=dadata;
   DAC_WR=0;
   delay(5);
   DAC_WR=1;
   DAC_CS=1; 
}

void AD0832out(uchar dadata)                       
{
  
   ADC_CS=0;
   P0=dadata;
   ADC_DI=0;
   delay(5);
   ADC_DO=1;
   ADC_CS=1; 
}

void keyscan()                                            
{  
   //增大电压
   if(key1==0)
   {
      delay(5);//消抖
      if(key1==0)
      {
	 while(key1==0);
	 volt++;
	 if(volt>=128) volt=128;
	 write_sfm(10,volt);
      }
   }
   //减小电压啊
   if(key2==0)
   {
      delay(5);//消抖
      if(key2==0)
      {
	 while(key2==0);
	 volt--;
	 if(volt=255) volt=0;
	 write_sfm(10,volt);
      }
   }
   //设置输出
   DA0832out(volt); 
}

void main()                                
{ 
 
  Init();  
  while(1)
   {
      DA0832out(volt);
     keyscan();									
   }
  while(1);
}

