#include<reg51.h>
#include<intrins.h>
#define uchar unsigned char
#define uint unsigned int
//测试
unsigned char code huan[]= // 欢
{
0x04,0x24,0x44,0x84,0x64,0x9C,0x40,0x30,0x0F,0xC8,0x08,0x08,0x28,0x18,0x00,0x00,
0x10,0x08,0x06,0x01,0x82,0x4C,0x20,0x18,0x06,0x01,0x06,0x18,0x20,0x40,0x80,0x00
};
unsigned char code ying[]= //迎
{
0x40,0x40,0x42,0xCC,0x00,0x00,0xFC,0x04,0x02,0x00,0xFC,0x04,0x04,0xFC,0x00,0x00,
0x00,0x40,0x20,0x1F,0x20,0x40,0x4F,0x44,0x42,0x40,0x7F,0x42,0x44,0x43,0x40,0x00
};
unsigned char code fang[]= //访
{
0x40,0x40,0x42,0xCC,0x00,0x08,0x08,0xF8,0x89,0x8E,0x88,0x88,0x88,0x08,0x08,0x00,
0x00,0x00,0x00,0x3F,0x90,0x48,0x30,0x0F,0x00,0x40,0x80,0x40,0x3F,0x00,0x00,0x00
};
unsigned char code wen[]=  //问
{
0x00,0xF8,0x01,0x02,0x00,0xE2,0x22,0x22,0x22,0xE2,0x02,0x02,0x02,0xFE,0x00,0x00,
0x00,0xFF,0x00,0x00,0x00,0x1F,0x08,0x08,0x08,0x1F,0x00,0x40,0x80,0x7F,0x00,0x00
};
unsigned char code yi[]=  //刘
{
0x08,0x28,0x48,0x89,0x0E,0x88,0x78,0x08,0x08,0x00,0xF8,0x00,0x00,0xFF,0x00,0x00,
0x40,0x20,0x10,0x09,0x06,0x19,0x60,0x00,0x00,0x00,0x0F,0x40,0x80,0x7F,0x00,0x00
};
unsigned char code ren[]= //航
{
0x80,0xFC,0x96,0xE5,0x84,0xFC,0x00,0x08,0xC8,0x49,0x4A,0xC8,0x08,0x08,0x00,0x00,
0x80,0x7F,0x02,0x4C,0x80,0x7F,0x80,0x60,0x1F,0x00,0x00,0x3F,0x40,0x40,0x78,0x00
};
unsigned char code qiao[]= 
{
0x10,0x0C,0x24,0x24,0x24,0x24,0x25,0xE6,0x24,0x24,0x24,0x24,0x24,0x14,0x0C,0x00,
0x02,0x02,0x02,0x02,0x02,0x42,0x82,0x7F,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x00
};
unsigned char code cui[]= 
{
0x00,0x00,0xF8,0x88,0x88,0x88,0x88,0xFF,0x88,0x88,0x88,0x88,0xF8,0x00,0x00,0x00,
0x00,0x00,0x1F,0x08,0x08,0x08,0x08,0x7F,0x88,0x88,0x88,0x88,0x9F,0x80,0xF0,0x00
};
unsigned char code bai[]=  
{
0x00,0x00,0xFE,0x02,0x82,0x82,0x82,0x82,0xFA,0x82,0x82,0x82,0x82,0x82,0x02,0x00,
0x80,0x60,0x1F,0x40,0x40,0x40,0x40,0x40,0x7F,0x40,0x40,0x44,0x58,0x40,0x40,0x00
};
unsigned char code du[]= 
{
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x36,0x36,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00

};
unsigned char code kong[]= 
{
0x00,0xE0,0x10,0x08,0x08,0x10,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x0F,0x10,0x20,0x20,0x10,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};
unsigned char code jian[]= 
{
0x08,0x78,0x88,0x00,0x00,0xC8,0x38,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x07,0x38,0x0E,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};
sbit CS1=P2^0;//片选1,低电平有效，CS1=0开左屏幕，CS1=1关左屏幕
sbit CS2=P2^1;//片选2，低电平有效，CS2=0开右屏幕，CS2=1关右屏幕
sbit RS=P2^2;//数据，指令选择信号，RS=1为数据操作，RS=0为写指令或读状态（一般为读忙标志）
sbit RW=P2^3;//读写选择信号，RW=1为读选通，RW=0为写选通
sbit EN=P2^4;//读写使能信号
void busy()//忙检测函数
{P0=0X00; //这句不能少
RS=0; 
RW=1;
EN=1;
while(P0&0X80);//P0&0X80结果为真则一直执行空操作，也就是说P0&0X80为0则结束循环
EN=0;
}
void wcmd(uchar cmd)
{busy(); //每次写入指令或数据之前都进行忙检测
RS=0;
RW=0;
P0=cmd;
EN=1;_nop_();_nop_();//在EN下降沿写入数据和指令
EN=0;
}
void wdata(uchar dat) //写命令和写数据只在RS=0或RS=1上不同，其余都相同
{busy();
RS=1;
RW=0;
P0=dat;
EN=1;_nop_();_nop_();//在EN下降沿写入数据和指令
EN=0;
}
void set_page(uchar page)//设置页，12864LCD共有8页，每页有8行点阵点。
{page=0xb8|page;  //首页地址为0XB8
wcmd(page);		  //page取值范围为0~7,表示第1到8页
}
void set_line(uchar line)//设置显示的起始行，共有0——63行，一般从0行开始显示
{line=0xc0|line;  //起始行地址0XC0
wcmd(line);	//line取值范围为0~63，表示第1到64行
}
void set_column(uchar column)//设置显示的列
{//column=column&0x3f; //列的最大值为0X3F，即64
column=0x40|column;	 //列的首地址为0X40,
wcmd(column);		 //column的取值范围为0~63，共64列
}
void set_onoff(uchar onoff)//设置显示开关，onoff取值为0或1
{onoff|=0x3e;//0X3E是关显示，0X3F是开显示
wcmd(onoff);//所以若onoff为0，则表示关显示，onoff为1，则表示开显示
}
void select_screen(uchar screen)//选屏，screen取值范围为0,1,2
{switch(screen)
{case 0:CS1=0;CS2=0;break; //全屏
case 1:CS1=0;CS2=1;break;  //左半屏
case 2:CS1=1;CS2=0;break;  //右半屏
default:break;
}
}
void clear_screen(uchar screen)//清屏
{uchar i,j;
select_screen(screen);//先选屏
for(i=0;i<8;i++)//控制页数0——7，共8页
{set_page(i);//设置页
set_column(0); //设置列，每页都从第1列开始，共64列
for(j=0;j<64;j++)//控制列数0——63，共64列
wdata(0x00);//写入0，列地址指针会自动加1 
}
}
void init()	//LCD初始化
{busy(); //忙检测
select_screen(0);//选屏，全屏
set_onoff(0);	//关显示
select_screen(0); //选屏，全屏
set_onoff(1);	  //开显示
select_screen(0); //选屏，全屏
clear_screen(0);  //清屏
set_line(0);	  //起始行：0
}
void show(uchar screen,uchar page,uchar column,uchar *p)//显示一个汉字，一个汉字有32字节数据 
{uchar i;	//screen表示选择屏幕，page表示页，column表示列，*p表示汉字的数组
select_screen(screen); //选屏
set_page(page);	   //设置页，写上半页
set_column(column);//设置列
for(i=0;i<16;i++) //控制16列的数据输出
wdata(p[i]);   //汉字的上半部分
set_page(page+1); //写下半页
set_column(column);	//控制列
for(i=0;i<16;i++) //控制16列的数据输出
wdata(p[i+16]);	 //汉字的下半部分
}
void main()
{init();  //LCD初始化
clear_screen(0); //清屏
set_line(0);   //显示开始行
//1表示左屏显示，0表示从0页开始显示。因为一页只有8行点，
//而显示一个汉字需要16行点（整屏有64行点），所以显示一个汉字需要2页
//第0页显示“欢”字的上半部分，第1页显示“欢”汉字的下半部分
//2*16表示从第32列开始显示，前面空出0~31列（即2个字的位置）
show(1,0,2*16,huan);//欢
//1表示左屏显示，0表示从0页开始显示
//3*16表示从第48列开始显示，前面空出0~477列（即3个汉字的位置）
show(1,0,3*16,ying);//迎
//2表示右屏显示，0表示从0页开始显示
//0*16表示从第0列开始显示（即第一个汉字的位置）
show(2,0,0*16,fang);//访
//1*16表示从第16列开始显示，前面空出0~15列（即一个汉字的位置）
show(2,0,1*16,wen);	 //问
//左屏开，从第3页（共8页）第0列开始显示，即第3，4页显示”伊人憔悴百度空间“几个字
show(1,2,0*16,yi);	 
show(1,2,1*16,ren);	 
show(1,2,2*16,qiao); 
show(1,2,3*16,cui);	 
show(2,2,0*16,bai);	 
show(2,2,1*16,du);	 
show(2,2,2*16,kong); 
show(2,2,3*16,jian); 
while(1);
}
