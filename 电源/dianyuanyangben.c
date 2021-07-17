#include<reg52.h>

#define uchar unsigned char
#define uint  unsigned int
sbit key1=P1^0;                                      //�˿ڶ���,ѡ�����ڸ�λ��ʮλ 
sbit key2=P1^1;                                     //��괦��ѹΪ1��� 
sbit rs=P1^4;
sbit en=P1^5;
sbit DAC_CS=P3^2;
sbit DAC_WR=P3^6;
sbit ADC_CS=P0^0;
sbit ADC_DI=P0^1;
sbit ADC_DO=P0^2;
uchar code table1[]="  liu do";                 //��ʼ����ʾ
uchar code table2[]="  dianya :0.0V ";                //��ʼ����Դ
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
    write_com(0x38);                          //�õ�ַ
	write_com(0x0c);                            
	write_com(0x06);                          //�������
	write_com(0x01);                          //����ʾ
	write_com(0x80);                          //lcd DDRAM����
     for(num=0;num<16;num++)
		{
			write_date(table1[num]);
			delay(50);
		}
	write_com(0x80+0x40);                    //lcd�ڶ���                 
	for(num=0;num<14;num++)
		{
			write_date(table2[num]);
			delay(50);
		}
}

void write_voltage(uchar add,uchar dat)            
   { 
     write_com(0x80+0x40+add);                      //ȷ���ڶ���λ��
     write_date(0x30+dat);                          //д����
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
   //�����ѹ
   if(key1==0)
   {
      delay(5);//����
      if(key1==0)
      {
	 while(key1==0);
	 volt++;
	 if(volt>=128) volt=128;
	 write_sfm(10,volt);
      }
   }
   //��С��ѹ��
   if(key2==0)
   {
      delay(5);//����
      if(key2==0)
      {
	 while(key2==0);
	 volt--;
	 if(volt=255) volt=0;
	 write_sfm(10,volt);
      }
   }
   //�������
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

