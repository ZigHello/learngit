#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <Math.h>

#pragma warning(disable:4996)

#define High 480
#define Width 640
#define PI 3.14159
//#define Title "我的时钟"
//#define Note "[时针：红色] [分针：黄色] [秒针：白色]"
int main()
{
	initgraph(Width, High);
	int center_x, center_y;  //中心坐标，秒针的起始坐标
	center_x = Width/2;
	center_y = High/2;

	int secondLength;   //秒针的长度
	int minuteLength;   //分针的长度
	int hourLength;     //时针的长度
	secondLength = Width / 5;
	minuteLength = Width / 6;
	hourLength = Width / 8;

	int secondEnd_x, secondEnd_y;     //秒钟的终点坐标
	int minuteEnd_x, minuteEnd_y;     //分针的终点坐标
	int hourEnd_x, hourEnd_y;		  //时针的终点坐标


	float secondAngle = 0;//秒针对应转动角度
	float minuteAngle = 0;//分针对应转动角度
	float hourAngle = 0;//时针对应转动角度

	SYSTEMTIME ti;  //定义变量存储系统时间
	BeginBatchDraw();
	while (1)
	{
		//绘制表盘边缘
		setlinestyle(PS_SOLID, 2); 
		setcolor(WHITE);
		circle(center_x, center_y, Width / 4);
		
		//绘制刻度
		int x, y;
		for (int i = 0; i < 60; i++)
		{
			x = center_x + int(Width / 4.5 * sin(i * 2 * PI / 60));
			y = center_y + int(Width / 4.5 * cos(i * 2 * PI / 60));
			if (i % 15 == 0) //0,15,30,45,60
			{
				bar(x - 5, y + 5, x + 5, y - 5);
			}
			else if (i % 5 == 0) //5,10,20,25,35,40,50,55
			{
				circle(x, y, 3);
			}
			else {
				putpixel(x, y, WHITE);
			}
		}

		outtextxy(center_x-20 , center_y + Width/6, "我的时钟");

		GetLocalTime(&ti);
		secondAngle = (double)ti.wSecond * 2 * PI / 60;   //一圈的角度为2PI，一圈60秒，一秒钟走过的角度为2*PI/60
		minuteAngle = (double)ti.wMinute * 2 * PI / 60;  //一分钟走过的角度为2*PI/60
		hourAngle = (double)ti.wHour * 2 * PI / 12;		//一小时走过的角度为2*PI/12

		//角度决定秒针终点坐标
		secondEnd_x = (int)center_x + secondLength * sin(secondAngle);
		secondEnd_y = (int)center_y - secondLength * cos(secondAngle);
		//角度决定分针终点坐标
		minuteEnd_x = (int)center_x + minuteLength * sin(minuteAngle);
		minuteEnd_y = (int)center_y - minuteLength * cos(minuteAngle);
		//角度决定时针终点坐标
		hourEnd_x = (int)center_x + hourLength * sin(hourAngle);
		hourEnd_y = (int)center_y - hourLength * cos(hourAngle);

		//画秒针
		setlinestyle(PS_SOLID, 2);  //画实线，宽度为2个像素
		setcolor(WHITE);
		line(center_x, center_y, secondEnd_x, secondEnd_y);
		//画分针
		setlinestyle(PS_SOLID, 4);  //画实线，宽度为4个像素
		setcolor(YELLOW);
		line(center_x, center_y, minuteEnd_x, minuteEnd_y);
		//画时针
		setlinestyle(PS_SOLID, 6);  //画实线，宽度为6个像素
		setcolor(RED);
		line(center_x, center_y, hourEnd_x, hourEnd_y);

		FlushBatchDraw();
		Sleep(50);

		//隐藏前面一帧的秒针
		setcolor(BLACK);
		line(center_x, center_y, secondEnd_x, secondEnd_y);
		line(center_x, center_y, minuteEnd_x, minuteEnd_y);
		line(center_x, center_y, hourEnd_x, hourEnd_y);
	}
	EndBatchDraw();
	getch();
	closegraph();

	return 0;
}